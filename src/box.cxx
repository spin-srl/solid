#include <Fl/fl_draw.H>
#include "box.h"

Box::Box(int x, int y, int w, int h, const char *name) : Group(x, y, w, h, nullptr, name) {}

Measure Box::layout() {
    auto cc = Fl::cairo_cc();

    using namespace std;

    const auto isVertical = direction == Vertical;

    int all = isVertical ? h() : w();
    int otherAxis = 0;
    int available = isVertical ? all - margin.Vertical() : all - margin.Horizontal();
    available -= max(0.0, (children() - 1) * spacing);

    vector<SolidBase *> second_pass;

    int offset = isVertical ? margin.top + padding.top : margin.left + padding.left;

    for (int i = 0; i < children(); ++i) {
        auto *item = dynamic_cast<SolidBase *>(child(i));
        Measure m{};

//        if (item->boxAlign != BoxAlign::Fill) {
        m = item->layout();
//        } else {
//            second_pass.push_back(item);
//        }

        if (isVertical) {
            if (item->boxAlign == Fill)
                m.Width = w() - padding.Horizontal();

            item->as_widget()->resize(x() + padding.left + margin.left, y() + offset,
                                      (int) m.Width,
                                      (int) m.Height);
        } else {
            if (item->boxAlign == Fill)
                m.Height = h() - padding.Vertical();

            item->as_widget()->resize(x() + offset, y() + padding.top + margin.top,
                                      (int) m.Width,
                                      (int) m.Height);
        }

        available -= isVertical ? m.Height : m.Width;
//        available -= spacing;

        if (otherAxis < (isVertical ? m.Height : m.Width) + spacing) {
            otherAxis = (isVertical ? m.Width : m.Height) + spacing;
        }

        offset += (isVertical ? m.Height : m.Width) + spacing;
    }

//    int slice_to_share;
//    if (available > 0) {
//        available / second_pass.size();
//    }

//    for (SolidBase *item = second_pass.back(); !second_pass.empty(); second_pass.pop_back()) {
//        item->layout(cc);
//    }
//
//    if (available < 0) {
//        if (isVertical) {
//            Fl_Widget::size(w(), h() - available);
//            return Measure{w(), h() - available};
//        } else {
//            Fl_Widget::size(w() - available, h());
//            return Masure{w() - available, h()};
//        }
//    }

    int growX = 0, growY = 0;
    if (isVertical && available < 0) {
        if (otherAxis > w()) {
            growX = otherAxis - w();
        }
        growY = -available;
    } else {
        if (otherAxis > h()) {
            growY = otherAxis - h();
        }
        growX = -available;
    }

    Fl_Widget::size(w() + growX, h() + growY);

    return {w(), y()};
}

void Box::draw() {
    Group::draw();
}

int Box::handle(int evt) {
    if (evt == FL_ENTER || evt == FL_LEAVE)
        redraw();

    return Fl_Group::handle(evt);
}

void Box::resize(int x, int y, int w, int h) {
    Group::resize(x, y, w, h);
    refreshLayout = true;
}
