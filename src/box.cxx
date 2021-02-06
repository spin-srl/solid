#include <Fl/fl_draw.H>
#include "box.h"

using namespace Solid;

Box::Box(int x, int y, int w, int h, const char *name) : Group(x, y, w, h, nullptr, name) {
    clip_children(true);
}

Measure Box::layout() {
    auto cc = Fl::cairo_cc();

    Fl_Group::resize(x(), y(), std::max(w(), 10), std::max(h(), 10));

    if (cc == nullptr)return Measure{};

    bool isVertical = direction == Vertical;

    double wholeMargin = isVertical ? this->margin.Vertical() : this->margin.Horizontal();
    double childSpacing = (children() <= 1) ? 0 : (children() - 1) * spacing;
    double available = (isVertical ? h() : w()) - wholeMargin - childSpacing;
    double otherAxis = 0;

    int offset = 0;
    int howManyChildrenHasExpandEnabled = 0;

    for (int child_id = 0; child_id < children(); ++child_id) {
        auto *c = dynamic_cast<SolidBase *>(child(child_id));
        if (c != nullptr && c->Expand)
            howManyChildrenHasExpandEnabled++;
    }

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

        flChild->resize(newX, newY, m.Width, m.Height);
    }

    double sliceOfPizza = available / howManyChildrenHasExpandEnabled;
    for (int child_id = 0; child_id < children(); ++child_id) {
        auto solidChild = dynamic_cast<SolidBase *>(child(child_id));
        auto widget = child(child_id);
        int newW = widget->w(), newH = widget->h();

        if (howManyChildrenHasExpandEnabled > 0 && solidChild && solidChild->Expand &&
            sliceOfPizza > widget->w()) {
            if (isVertical)
                newH = (int) sliceOfPizza;
            else
                newW = (int) sliceOfPizza;
        }

        int newPos = (int) (isVertical ? y() + margin.top : x() + margin.left);
        if (child_id > 0) {
            Fl_Widget *prevChild = child(child_id - 1);
            newPos += (int) (child_id * spacing) + isVertical ? (prevChild->y() + prevChild->h()) : (prevChild->x() +
                                                                                                     prevChild->w());
        }

        if (isVertical) {
            widget->resize(widget->x(), newPos, newW, newH);
        } else {
            widget->resize(newPos, widget->y(), newW, newH);
        }
    }

    //Reset available if greater than zero and there were widgets to fill the space
    if (howManyChildrenHasExpandEnabled > 0 && available > 0)
        available = 0;

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

void Box::draw() {
    Group::draw();
}
