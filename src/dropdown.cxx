#include "dropdown.h"
#include <Fl/Fl_Menu.H>
#include <FL/Fl_Window.H>

using namespace Solid;

//void DropDownPopup::draw() {
//    auto cc = Fl::cairo_make_current(this);
//
//    set_cairo_color(cc, SolidSkin::current->Surface);
//    round_rect(cc, x(), y(), w(), h(), 4);
//    cairo_fill_preserve(cc);
//    set_cairo_color(cc, SolidSkin::current->Primary);
//    cairo_stroke(cc);
//
//    Fl_Double_Window::draw();
//}

Fl_Image *roundshape(int w, int h, int r) {
    auto surf = cairo_image_surface_create(cairo_format_t::CAIRO_FORMAT_A8, w, h);
    auto scc = cairo_create(surf);

    cairo_set_source_rgb(scc, 0, 0, 0);
    cairo_rectangle(scc, -1, -1, w + 2, h + 2);
    cairo_stroke(scc);

    cairo_set_source_rgb(scc, 1, 1, 1);
    round_rect(scc, 0, 0, w, h, r);
    cairo_fill(scc);

    cairo_surface_flush(surf);
    auto ret = new Fl_RGB_Image(cairo_image_surface_get_data(surf), w, h, 1);
    cairo_surface_destroy(surf);

    return ret;
}

class __MenuWindow : public Fl_Window {
public:
    DropDown *dd;

    __MenuWindow(DropDown *dd) :
            Fl_Window(dd->x(), dd->y(), dd->w(), dd->Options->size() * 25) {

        clear_border();

        this->dd = dd;
    }

    void draw() {
        auto cc = Fl::cairo_make_current(this);
        auto gray = fl_color_average(SolidSkin::current->Surface, FL_GRAY, 0.8);
        int hovered = Fl::event_y() / 25;

        cairo_text_extents_t extents;

        cairo_set_font_face(cc, Solid::SolidSkin::fonts[1]);
        cairo_set_font_size(cc, 12);

        if (Fl::event_x() < 0 || Fl::event_x() > w() || hovered < 0 || hovered >= dd->Options->size())
            hovered = -1;

        for (int i = 0; i < dd->Options->size(); ++i) {
            auto prim = hovered == i ? fl_color_average(SolidSkin::current->Primary, FL_GRAY, 0.8)
                                     : SolidSkin::current->Primary;
            auto nonselected = hovered == i ? fl_color_average(gray, FL_GRAY, 0.8) : gray;

            cairo_text_extents(cc, dd->Options->at(i), &extents);
            set_cairo_color(cc, i == dd->selectedIndex ? prim : nonselected);
            cairo_rectangle(cc, 0, i * 25, w(), 25);
            cairo_fill(cc);

            set_cairo_color(cc, i == dd->selectedIndex ? SolidSkin::current->OnPrimary : SolidSkin::current->OnSurface);
            cairo_move_to(cc, 5, i * 25 + extents.height / 2 + 25 / 2);
            cairo_show_text(cc, dd->Options->at(i));
        }
    }

    int handle(int evt) {
        switch (evt) {
            case FL_MOVE:
                redraw();
                break;

            case FL_PUSH:
                return Fl_Window::handle(evt);

            case FL_RELEASE:
                hide();
                Fl::grab(nullptr);
                return Fl_Window::handle(evt);
        }

        return Fl_Window::handle(evt);
    }
};

DropDown::DropDown(int x, int y, int w, int h, const char *label, const char *name) :
        Solid::Button(x, y, w, h, label, name) {
    when(FL_WHEN_RELEASE);
    Type = ButtonType::Primary;

    padding={};

    callback([](Fl_Widget *w, void *ptr) {
        printf("Showing popup\n");
        auto dd = dynamic_cast<DropDown *>(w);
        auto mw = new __MenuWindow(dd);
        mw->show();
        mw->redraw();

        for (int i = 0; i < dd->Options->size(); ++i) {
            auto b = new Fl_Button(0, i * 25, dd->w(), 25, dd->Options->at(i));
            b->when(FL_WHEN_RELEASE);
            b->callback([](Fl_Widget *w, void *_arg) {
                auto arg = (std::pair<DropDown *, int> *) _arg;
                printf("Selecting %d\n", arg->second);
                arg->first->selectedIndex = arg->second;
            }, new std::pair<DropDown *, int>(dd, i));

            b->box(FL_FLAT_BOX);
            b->color((i == dd->selectedIndex) ? SolidSkin::current->Primary : fl_color_average(
                    SolidSkin::current->Surface, FL_GRAY, 0.8));
            b->labelcolor((i == dd->selectedIndex) ? SolidSkin::current->OnPrimary : SolidSkin::current->OnSurface);
            b->labelfont(i == dd->selectedIndex ? 1 : 0);
            mw->add(b);
        }

        Fl::grab(mw);
    });
}

void DropDown::draw() {
    auto cc = get_cc();

    if (cc != nullptr) {
        set_cairo_color(cc, buttonColor());
        round_rect(cc, x(), y(), w(), h(), 2);
        cairo_fill(cc);
        set_cairo_color(cc, SolidSkin::current->Surface);
        cairo_rectangle(cc, x() + 1, y() + 1, w() - 20, h() - 2);
        cairo_fill(cc);

        cairo_set_line_width(cc, 2);
        cairo_move_to(cc, x() + w() - 10, y() + h() / 2 + 3);
        cairo_rel_line_to(cc, -3, -5);
        cairo_move_to(cc, x() + w() - 10, y() + h() / 2 + 3);
        cairo_rel_line_to(cc, 3, -5);
        cairo_stroke(cc);

        if (selectedIndex != -1) {
            auto extents = calcExtents(cc, Options->at(selectedIndex));

            set_cairo_color(cc, active_r() ? SolidSkin::current->OnSurface : FL_GRAY);
            cairo_set_font_face(cc, SolidSkin::fonts[1]);
            cairo_set_font_size(cc, this->labelsize());
            cairo_move_to(cc, this->x() + 6, this->y() + this->h() / 2 + extents.height / 2);
            cairo_show_text(cc, Options->at(selectedIndex));
        }
    }
}

Measure DropDown::layout() {
    cairo_text_extents_t extents;

    auto cc = get_cc();

    if (cc == nullptr || selectedIndex == -1 || Options->size() == 0) {
        return Measure{100, 25};
    }

    char *text = Options->at(selectedIndex);
    cairo_set_font_face(cc, SolidSkin::fonts[1]);
    cairo_set_font_size(cc, labelsize());
    cairo_text_extents(cc, text, &extents);

    return Measure{20 + 20 + 2 + 2 + static_cast<int>(extents.width + padding.Horizontal()),
                   15 + static_cast<int>(extents.height + padding.Vertical())};
}
