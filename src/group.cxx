#include <vector>
#include "group.h"

Group::Group(int x, int y, int w, int h, const char *label, const char *name) :
        SolidBase(name),
        Fl_Group(x, y, w, h, label) {
//    end();

}

void Group::resize(int x, int y, int w, int h) {
    Fl_Widget::resize(x, y, w, h);
    refreshLayout=true;
    redraw();
}

void Group::draw() {
    layout();
    Fl_Group::draw();

    debugDraw();
}
