#include <FL/Fl.H>
#include <Fl/Fl_Widget.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Window.H>
#include <typeinfo>
#include <Fl/fl_draw.H>

class SolidBase;
class Widget;

class SolidBase{
public:
    const char* Name;

    void (*onDestroy)(SolidBase* w);

    SolidBase(const char* name){
        this->Name=name;
    }

    virtual ~SolidBase()
    {
            if (onDestroy != nullptr)
            {
                    onDestroy(this);
            }
    }

    char* Path(){
        Fl_Widget* w=dynamic_cast<Fl_Widget*>(this);
        if (w->parent()==nullptr)
            return strdup((char*)this->Name);

        SolidBase* solidparent=dynamic_cast<SolidBase*>(w->parent());
        if (solidparent==nullptr)
            return strdup((char*)this->Name);

        char* parentname=solidparent->Path();
        char* ret=(char*)malloc(strlen(parentname)+strlen(this->Name)+1);
        sprintf(ret,"%s/%s",(const char*)parentname,(const char*)this->Name);
        free((void*)parentname);

        return ret;
    }

    static bool get_next_child(char* path, char** cname, char** more)
    {
            if (path == nullptr || strlen(path) == 0)
            {
                    *cname = nullptr;
                    *more = nullptr;
                    return false;
            }

            if (path[0] == '/')
            {
                    path++;
            }

            char* nextchild = strchr(path, '/');

            if (nextchild == nullptr)
            {
                    *cname = path;
                    *more = nullptr;

                    return false;
            }
            else
            {
                    off64_t length = nextchild - path;
                    *cname = (char*)calloc(1, length + 1);
                    memcpy(*cname, path, length);
                    *more = nextchild + 1;
                    return true;
            }
    }

//        "Group0/Group1/Widget"
    virtual SolidBase* GetChild(const char* path)
    {
            Fl_Group* flgroup=dynamic_cast<Fl_Group*>(this);

            if (flgroup==nullptr || path == nullptr || flgroup->children()==0 || strlen(path) == 0)
            {
                    return nullptr;
            }

            char* cname;
            char* more;

            bool hasmore = get_next_child((char*)path, &cname, &more);

//            printf("Widget %s(%d children) queried for path '%s'\n", Name, flgroup->children(), path);
//            printf("CNAME: '%s'\n", cname ? cname : "(null)");
//            printf("MORE: '%s' HasMore: %s\n", more ? more : "(null)", hasmore ? "Yes" : "No");

            for (int i = 0; i < flgroup->children(); ++i)
            {
                    SolidBase*item=dynamic_cast<SolidBase*>(flgroup->child(i));
                    if (item==nullptr || item->Name==nullptr)
                        continue;

//                    printf("Comparing %s to %s\n",item->Name,cname);

                    if (strcmp(item->Name, cname) == 0)
                    {
//                        printf("Matches\n");
                            if (!hasmore)
                            {
//                                    printf("Returning widget '%s'(%s)\n", item->Name, flgroup->child(i)->label());
                                    return dynamic_cast<SolidBase*>(flgroup->child(i));
                            }

                            SolidBase* child_as_group=dynamic_cast<SolidBase*>(item);
                            if (child_as_group == nullptr)
                                continue;

                            return child_as_group->GetChild(more);
                    }
            }

            return nullptr;
    }
};

class Widget: public SolidBase, public Fl_Widget
{
  public:
        Widget(int x, int y, int w, int h, const char* label = nullptr, const char* name = nullptr):
                SolidBase(name),
                Fl_Widget(x, y, w, h, label)
        {
            this->Name = name;
        }
};

class Group: public SolidBase, virtual public Fl_Group
{
  public:
        Group(int x, int y, int w, int h, const char* label = nullptr, const char* name = nullptr):
                SolidBase(name),
                Fl_Group(x, y, w, h, label)
        {
            end();
        }

};

class Window: public SolidBase, virtual public Fl_Window
{
  public:
        Window(int x, int y, int w, int h, const char* label = nullptr, const char* name = nullptr):
                Fl_Window(x, y, w, h, label),
                SolidBase(name)
        {
        }
};

class Button: public SolidBase, public Fl_Button
{
  public:
        Button(int x, int y, int w, int h, const char* label = nullptr, const char* name = nullptr):
            SolidBase(name),
            Fl_Button(x, y, w, h, label)
        {
            labelcolor(FL_GRAY);
            labelsize(10);
        }

        int handle(int evt){
            switch(evt){
                case FL_PUSH:
                case FL_RELEASE:
                case FL_LEAVE:
                case FL_ENTER:
                    fl_cursor(Fl::belowmouse()==this?FL_CURSOR_HAND:FL_CURSOR_ARROW);
                    redraw();
                    break;
            }

            return Fl_Button::handle(evt);
        }

        void draw(){
            fl_rectf(x(),y(),w(),h(),parent()->color());

            Fl_Color color=Fl::belowmouse()==this?(Fl::event_button1()?FL_BLUE:FL_GREEN):FL_GRAY0;
            fl_color(color);
            fl_rect(x(),y(),w(),h());

            fl_font(labelfont(),labelsize());
            fl_draw(label(),x(),y(),w(),h(),align(),active()?image():deimage(),true);
        }
};
