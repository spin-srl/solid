#include <cassert>
#include "window.h"

Window::Window(int x, int y, int w, int h, const char *label, const char *name) :
        Fl_Double_Window(x, y, w, h, label),
        SolidBase(name) {
    color(SolidSkin::current->Surface);
//    end();
}

Measure Window::layout() {
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

void Window::draw() {
//    cairo_t *cc = Fl::cairo_make_current(this);

//    if (cc && refreshLayout) {
//        layout(cc);
//        refreshLayout=false;
//    }

    Fl_Window::draw();
}

