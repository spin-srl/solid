#include <Fl/fl_draw.H>
#include "box.h"

using namespace Solid;

Box::Box(int x, int y, int w, int h, const char *name) : Group(x, y, w, h, nullptr, name) {}

Measure Box::layout() {
    auto cc = Fl::cairo_cc();

    Fl_Group::resize(x(), y(), std::max(w(), 10), std::max(h(), 10));
//    Fl_Group::resize(x(),y(),w(),h());

    if (cc == nullptr)return Measure{};

    bool isVertical = direction == Vertical;

    double wholeMargin = isVertical ? this->margin.Vertical() : this->margin.Horizontal();
    double childSpacing = (children() <= 1) ? 0 : (children() - 1) * spacing;
    double available = (isVertical ? h() : w()) - wholeMargin - childSpacing;
    double otherAxis = 0;

    int offset = 0;

    for (int child_id = 0; child_id < children(); ++child_id) {
        Fl_Widget *flChild = child(child_id);
        auto solidChild = dynamic_cast<SolidBase *>(flChild);

        Measure m = solidChild ? solidChild->layout() : Measure{flChild->w(), flChild->h()};

        int newX = (int) (x() + this->margin.left);
        int newY = (int) (y() + this->margin.top);

        if (isVertical) {
            newY += offset;
            m.Width = std::max(m.Width, w() - this->margin.Horizontal());
            available -= m.Height;
            otherAxis = std::max(otherAxis, m.Width + wholeMargin);
        } else {
            newX += offset;
            m.Height = std::max(m.Height, h() - this->margin.Vertical());
            available -= m.Width;
            otherAxis = std::max(otherAxis, m.Height + wholeMargin);
        }

        offset += (int) (isVertical ? m.Height : m.Width);
        offset += (int) spacing;

//        printf("x: %d, y: %d, NewX: %d newY: %d\n", x(), y(), newX, newY);
        flChild->resize(newX, newY, m.Width, m.Height);
    }

    int growX = 0;
    int growY = 0;

    if (available < 0) {
        if (isVertical) {
            growY = -available;
            if (otherAxis > w()) {
                growX = otherAxis - w();
            }
        } else {
            growX = -available;
            if (otherAxis > h()) {
                growY = otherAxis - h();
            }
        }
    }

    auto newSize = Measure{w() + growX, h() + growY};

    return newSize;
}

void Box::resize(int x, int y, int w, int h) {
    Group::resize(x, y, w, h);
    refreshLayout = true;
}
