#include "ctype.h"
#include <cairo.h>
#include <Fl/Fl_Cairo.H>
#include <Fl/Fl_Group.H>
#include "button.h"
#include <Fl/fl_draw.H>
#include <string>
#include "solidbase.h"
#include "box.h"
#include "window.h"

using namespace Solid;

bool SolidBase::initialized = false;

SolidBase::SolidBase(const char *name) {
//    assert(name != nullptr);
    if (name == nullptr)
        name = "(null)";

    this->Name = name;
}

SolidBase::~SolidBase() {
    if (onDestroy != nullptr) {
        onDestroy(this);
    }
}

char *SolidBase::Path() {
    Fl_Widget *w = dynamic_cast<Fl_Widget *>(this);

    if (w->parent() == nullptr) {
        return (char *) this->Name;
    }

    SolidBase *solidParent = dynamic_cast<SolidBase *>(w->parent());

    if (solidParent == nullptr) {
        return (char *) this->Name;
    }

    char *parentName = solidParent->Path();

    char *ret = (char *) malloc(strlen(parentName) + strlen(this->Name) + 1);
    sprintf(ret, "%s/%s", (const char *) parentName, (const char *) this->Name);

    return ret;
}

bool SolidBase::get_next_child(char *path, char **cname, char **more) {
    if (path == nullptr || strlen(path) == 0) {
        *cname = nullptr;
        *more = nullptr;
        return false;
    }

    if (path[0] == '/') {
        path++;
    }

    char *nextchild = strchr(path, '/');

    if (nextchild == nullptr) {
        *cname = path;
        *more = nullptr;

        return false;
    } else {
        off64_t length = nextchild - path;
        *cname = (char *) calloc(1, length + 1);
        memcpy(*cname, path, length);
        *more = nextchild + 1;
        return true;
    }
}

SolidBase *SolidBase::GetChild(const char *path) {
    Fl_Group *flgroup = dynamic_cast<Fl_Group *>(this);

    if (flgroup == nullptr || path == nullptr || flgroup->children() == 0 || strlen(path) == 0) {
        return nullptr;
    }

    char *cname;
    char *more;

    bool hasmore = get_next_child((char *) path, &cname, &more);

    //            printf("Widget %s(%d children) queried for path '%s'\n", Name, flgroup->children(), path);
    //            printf("CNAME: '%s'\n", cname ? cname : "(null)");
    //            printf("MORE: '%s' HasMore: %s\n", more ? more : "(null)", hasmore ? "Yes" : "No");

    for (int i = 0; i < flgroup->children(); ++i) {
        SolidBase *item = dynamic_cast<SolidBase *>(flgroup->child(i));

        if (item == nullptr || item->Name == nullptr) {
            continue;
        }

        //                    printf("Comparing %s to %s\n",item->Name,cname);

        if (strcmp(item->Name, cname) == 0) {
            //                        printf("Matches\n");
            if (!hasmore) {
                //                                    printf("Returning widget '%s'(%s)\n", item->Name, flgroup->child(i)->label());
                return dynamic_cast<SolidBase *>(flgroup->child(i));
            }

            auto *child_as_group = dynamic_cast<SolidBase *>(item);

            if (child_as_group == nullptr) {
                continue;
            }

            return child_as_group->GetChild(more);
        }
    }

    return nullptr;
}

void SolidBase::debugDraw() {
    return;
    cairo_t *cc = Fl::cairo_cc();
    if (cc == nullptr)return;

    Fl_Widget *w = this->as_widget();

    cairo_set_source_rgba(cc, 1, 0, 0, 0.5);
    cairo_set_line_width(cc, 1);

    cairo_rectangle(cc, w->x(), w->y(), w->w(), w->h());
    cairo_stroke(cc);

    return;

    int namew = 0, nameh = 0;

    cairo_set_font_face(cc, SolidSkin::current->fonts[0]);
    cairo_text_extents_t extents;
    char *path = this->Path();
    cairo_text_extents(cc, path, &extents);

    namew = extents.width;
    nameh = extents.height;

    cairo_rectangle(cc, w->x(), w->y() - nameh, namew, nameh);
    cairo_fill(cc);

    cairo_set_source_rgb(cc, 1, 1, 1);

    cairo_move_to(cc, w->x() + w->w() / 2 - namew / 2, w->y() + w->h() / 2 - nameh / 2);
    printf(this->Path());
    cairo_show_text(cc, this->Path());
}

Fl_Widget *SolidBase::as_widget() {
    return dynamic_cast<Fl_Widget *>(this);
}

void SolidBase::fitIn(Fl_Widget *w, int margin) {
    this->as_widget()->resize(w->x() + margin, w->y() + margin, w->w() - (margin * 2), w->h() - (margin * 2));
}

bool SolidBase::initialize() {
    if (initialized)
        return false;

    SolidSkin::initialize();

    initialized = true;

    return true;
}

Measure SolidBase::layout() {
    refreshLayout = false;
    return Measure{as_widget()->w(), as_widget()->h()};
}

cairo_t *SolidBase::get_cc() {
    Fl_Widget *w = as_widget();
    while (w->parent() != nullptr)
        w = w->parent();
    auto *window = dynamic_cast<Solid::Window *>(w);
    return window == nullptr ? Fl::cairo_make_current(w->as_window()) : window->cc;
}
