#include "solidbase.h"

bool SolidBase::initialized=false;

SolidBase::SolidBase(const char* name)
{
    this->Name = name;
}

SolidBase::~SolidBase()
{
    if (onDestroy != nullptr)
    {
        onDestroy(this);
    }
}

char* SolidBase::Path()
{
    Fl_Widget* w = dynamic_cast<Fl_Widget*>(this);

    if (w->parent() == nullptr)
    {
        return strdup((char*)this->Name);
    }

    SolidBase* solidparent = dynamic_cast<SolidBase*>(w->parent());

    if (solidparent == nullptr)
    {
        return strdup((char*)this->Name);
    }

    char* parentname = solidparent->Path();
    char* ret = (char*)malloc(strlen(parentname) + strlen(this->Name) + 1);
    sprintf(ret, "%s/%s", (const char*)parentname, (const char*)this->Name);
    free((void*)parentname);

    return ret;
}

bool SolidBase::get_next_child(char* path, char** cname, char** more)
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

SolidBase* SolidBase::GetChild(const char* path)
{
    Fl_Group* flgroup = dynamic_cast<Fl_Group*>(this);

    if (flgroup == nullptr || path == nullptr || flgroup->children() == 0 || strlen(path) == 0)
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
        SolidBase* item = dynamic_cast<SolidBase*>(flgroup->child(i));

        if (item == nullptr || item->Name == nullptr)
        {
            continue;
        }

        //                    printf("Comparing %s to %s\n",item->Name,cname);

        if (strcmp(item->Name, cname) == 0)
        {
            //                        printf("Matches\n");
            if (!hasmore)
            {
                //                                    printf("Returning widget '%s'(%s)\n", item->Name, flgroup->child(i)->label());
                return dynamic_cast<SolidBase*>(flgroup->child(i));
            }

            SolidBase* child_as_group = dynamic_cast<SolidBase*>(item);

            if (child_as_group == nullptr)
            {
                continue;
            }

            return child_as_group->GetChild(more);
        }
    }

    return nullptr;
}
