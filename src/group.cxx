#include <vector>
#include <Fl/fl_draw.H>
#include "group.h"

using namespace Solid;

Group::Group(int x, int y, int w, int h, const char *label, const char *name) :
        SolidBase(name),
        Fl_Group(x, y, w, h, label) {
//    end();

}

void Group::resize(int x, int y, int w, int h) {
    Fl_Widget::resize(x, y, w, h);
    refreshLayout = true;
    layout();
    redraw();
}

void Group::draw() {
    fl_rectf(x(), y(), w(), h(), SolidSkin::current->Surface);
    Fl_Group::draw();
    debugDraw();
}
