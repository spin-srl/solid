#include <cassert>
#include <Fl/fl_draw.H>
#include "window.h"

using namespace Solid;

Solid::Window::Window(int x, int y, int w, int h, const char *label, const char *name) :
        Fl_Double_Window(x, y, w, h, label),
        SolidBase(name) {
    color(SolidSkin::current->Surface);
//    end();
}

Measure Solid::Window::layout() {
//    cairo_t *context = Fl::cairo_make_current(this->as_window());
//
//    auto c = dynamic_cast<SolidBase *>(child(0));
//    if (c != nullptr) {
//        c->as_widget()->size(w(), h());
//        auto m = c->layout(context);
//        if (m.Width < w())
//            m.Width = w();
//        if (m.Height < h())
//            m.Height = h();
//
//        size(m.Width, m.Height);
//    }
//
//    return Measure{w(), h()};
}
void Solid::Window::draw() {
//    fl_rectf(x(), y(), w(), h(), SolidSkin::current->Surface);

    for (int child_id = 0; child_id < children(); ++child_id) {
        auto _child = dynamic_cast<SolidBase *>(child(child_id));
        if (_child != nullptr) {
            auto m = _child->layout();

            _child->as_widget()->resize(_child->as_widget()->x(),
                                        _child->as_widget()->y(),
                                        (int) m.Width,
                                        (int) m.Height);
        }
    }
    Fl_Window::draw();
}

char *Solid::Window::Path() {
    return (char *) this->Name;
}