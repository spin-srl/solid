#include <Fl/fl_draw.H>
#include <Fl/Fl_Image_Surface.H>
#include <button.h>
#include "window.h"

#define WW Fl_Double_Window::w()
#define WH Fl_Double_Window::h()

using namespace Solid;

//cairo_font_face_t *Solid::Window::TitleFont = cairo_toy_font_face_create("Roboto",
//                                                                         cairo_font_slant_t::CAIRO_FONT_SLANT_NORMAL,
//                                                                         cairo_font_weight_t::CAIRO_FONT_WEIGHT_NORMAL);

Solid::Window::Window(int x, int y, int w, int h, const char *label, const char *name) :
        Fl_Double_Window(x, y, w, h, label),
        SolidBase(name) {
    color(SolidSkin::current->Surface);
//    clear_border();

//    this->Content = new Group(0, titleHeight, w, h - titleHeight);
//    this->Content->clip_children(1);
//    Fl_Double_Window::resizable(this->Content);
//    Fl_Double_Window::add(this->Content);
//    Fl_Group::current(this->Content);
//    this->Content->begin();

//    surf = cairo_image_surface_create(cairo_format_t::CAIRO_FORMAT_A8, WW, WH);
//    scc = cairo_create(surf);
//
//    cairo_set_source_rgb(scc, 0, 0, 0);
//    cairo_rectangle(scc, -1, -1, WW + 2, WH + 2);
//    cairo_stroke(scc);
//
//    cairo_set_source_rgb(scc, 1, 1, 1);
//    round_rect(scc, 0, 0, WW, WH, 5);
//    cairo_fill(scc);
//
//    cairo_surface_flush(surf);
//
//    windowShapeImage = new Fl_RGB_Image(cairo_image_surface_get_data(surf), WW, WH, 1);
//    shape(windowShapeImage);
}

Measure Solid::Window::layout() {
}

void Solid::Window::show() {
    updateLayout();
    Fl_Double_Window::show();
}

void Solid::Window::draw() {
    this->cc = Fl::cairo_make_current(this);

    //Clear  background
    cairo_rectangle(cc, 0, 0, Fl_Double_Window::w(), Fl_Double_Window::h());
    set_cairo_color(cc, SolidSkin::current->Surface);
    cairo_fill(cc);

    updateLayout();

    ///Content
//    Fl_Double_Window::draw();
    for (int child_id = 0; child_id < children(); ++child_id) {
        child(child_id)->draw();
    }
//    this->Content->draw();


    //////////////////////////////////
    ///Decorators
    //////////////////////////////////

    //Set font properties
//    cairo_set_font_face(cc, TitleFont);
//    cairo_set_font_size(cc, 12);

    //calc title's extents
//    cairo_text_extents_t titleExtents;
//    cairo_text_extents(cc, label(), &titleExtents);

    //Draw title
//    cairo_move_to(cc, 10, titleHeight / 2.0 + titleExtents.height / 2);
//    set_cairo_color(cc, SolidSkin::current->OnSurface);
//    cairo_show_text(cc, label());
    //////////////////////////////////

    //To Debug Content Widget's extents
    //    fl_rect(this->Content->x(),this->Content->y(),this->Content->w(),this->Content->h(),FL_RED);
}

void Solid::Window::updateLayout() const {
//    this->Content->layout();

//        for (int child_id = 0; child_id < children(); ++child_id) {
//        auto _child = dynamic_cast<SolidBase *>(child(child_id));
//        if (_child != nullptr) {
//            auto m = _child->layout();
//
//            _child->as_widget()->resize(_child->as_widget()->x(),
//                                        _child->as_widget()->y(),
//                                        (int) m.Width,
//                                        (int) m.Height);
//        }
//    }
}

char *Solid::Window::Path() {
    return (char *) this->Name;
}

void Solid::Window::resize(int x, int y, int w, int h) {
//    int requiredWidth = 0;
//    int requiredHeight = 0;
//    for (int i = 0; i < Content->children(); ++i) {
//        auto c = Content->child(i);
//        requiredWidth += c->w();
//        requiredHeight += c->h();
//    }
//    requiredWidth += this->padding.Horizontal();
//    if (requiredWidth > w) {
//        w = requiredWidth;
//    }

    Fl_Double_Window::resize(x, y, w, h);
}

//char *printDragType(Window::DragType type) {
//    const std::vector<const char *> names = {"None", "Move", "ResizeWidth", "ResizeHeight"};
//    printf("DragType: %d: ", type);
//    for (int i = 0; i < names.size(); ++i) {
//        printf("%s: [%c]\t", names[i], (type & 1 << (i - 1)) ? 'X' : ' ');
//    }
//    printf("\n");
//}

//int Window::handle(int event) {
//    switch (event) {
//        case FL_PUSH:
//            if (Fl::event_clicks() && Fl::belowmouse() == this) {
//                if (fullscreen_active())
//                    fullscreen_off();
//                else
//                    fullscreen();
//
//                return Fl_Double_Window::handle(event);
//            }
//
//            Drag = None;
//
//            if (Fl::event_x() > w() - 10)
//                Drag = DragType::ResizeWidth;
//
//            if (Fl::event_y() > h() - 10)
//                Drag = static_cast<DragType>(Drag | ResizeHeight);
//
//            if (Drag == None && Fl::belowmouse() == this)
//                Drag = Move;
//
////            printDragType(Drag);
//
//            xoff = this->x() - Fl::event_x_root();
//            yoff = this->y() - Fl::event_y_root();
//
//            Fl_Double_Window::handle(event);
//            return 1;
//
//        case FL_DRAG:
//            if (Drag & Move) {
//                this->position(xoff + Fl::event_x_root(), yoff + Fl::event_y_root());
//            } else {
//                int newW = w() + padding.Horizontal(), newH = h() + padding.Vertical();
//
//                if (Drag & ResizeWidth)
//                    newW = Fl::event_x() + 5;
//                if (Drag & ResizeHeight)
//                    newH = Fl::event_y() + 5;
//
//                if (newW != w() || newH != h())
//                    this->size(newW, newH);
//            }
//
//            this->redraw();
//            break;
//
//        case FL_RELEASE:
//            this->show();
//            break;
//    }
//
//    return Fl_Double_Window::handle(event);
//}

//void Window::add(Fl_Widget *w) {
//    w->position(w->x(), w->y() + titleHeight);
//    this->Content->add(w);
//}
//
//int Window::w() {
//    return Fl_Double_Window::w() - padding.Horizontal();
//}

//int Window::h() {
//    return Fl_Double_Window::h() - titleHeight - padding.Vertical();
//}

//void Window::resizable(Fl_Widget *w) {
//    this->Content->resizable(w);
//}

//Fl_Widget *Window::resizable() {
//    return this->Content->resizable();
//}
