#include "button.h"
#include "Fl/fl_draw.H"
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Cairo.H>
#include <cairo/cairo.h>

Button::Button(int x, int y, int w, int h, const char *l, const char *name) :
        SolidBase(name),
        Fl_Button(x, y, w, h, l) {
    this->labelfont(1);
    this->labelsize(12);
    this->label(l);
}

int Button::handle(int evt) {
    switch (evt) {
        case FL_PUSH:
        case FL_RELEASE:
        case FL_LEAVE:
        case FL_ENTER:
            fl_cursor(Fl::belowmouse() == this ? FL_CURSOR_HAND : FL_CURSOR_ARROW);
            redraw();
            break;
    }

    return Fl_Button::handle(evt);
}

const double degree_to_radian = 3.14159265358979 / 180.0;

inline void round_rect(cairo_t *cc, int x, int y, int w, int h, double r) {
    cairo_move_to(cc, x, y + r);
    cairo_arc(cc, x + r, y + r, r, 180 * degree_to_radian, 270 * degree_to_radian);
    cairo_line_to(cc, x + w - r, y);
    cairo_arc(cc, x + w - r, y + r, r, -90 * degree_to_radian, 0 * degree_to_radian);
    cairo_line_to(cc, x + w, y + h - r);
    cairo_arc(cc, x + w - r, y + h - r, r, 0 * degree_to_radian, 90 * degree_to_radian);
    cairo_line_to(cc, x + r, y + h);
    cairo_arc(cc, x + r, y + h - r, r, 90 * degree_to_radian, 180 * degree_to_radian);
    cairo_line_to(cc, x, y + r);
}

inline void set_cairo_color(cairo_t *cc, Fl_Color c) {
    uchar r, g, b;
    Fl::get_color(c, r, g, b);
    cairo_set_source_rgb(cc, r / 255.0, g / 255.0, b / 255.0);
}

void Button::draw() {
    cairo_t *cc = Fl::cairo_make_current(Fl::first_window());

    fl_rectf(x(), y(), w(), h(), SolidSkin::current->Surface);

    bool hovered = Fl::belowmouse() == this;
    bool clicked = Fl::event_button1();

    Fl_Color textcolor = hovered ? fl_lighter(SolidSkin::current->Primary) : SolidSkin::current->Primary;

    switch (Type) {
        case Outline:
            Fl_Color outlinecolor;
            Fl_Color target;

            outlinecolor = SolidSkin::current->Surface;
            target = fl_contrast(FL_WHITE, SolidSkin::current->Surface);

            outlinecolor = fl_color_average(outlinecolor, target, 0.8);
            set_cairo_color(cc, outlinecolor);
            cairo_set_line_width(cc, 0.6);

            round_rect(cc, x(), y(), w(), h(), 2);

            cairo_stroke(cc);

            break;

        case Primary:
            textcolor = hovered ? fl_lighter(SolidSkin::current->OnPrimary) : SolidSkin::current->OnPrimary;
            Fl_Color clickedcolor;
            clickedcolor = clicked ? fl_darker(SolidSkin::current->Primary) : fl_lighter(SolidSkin::current->Primary);
            clickedcolor = hovered ? clickedcolor : SolidSkin::current->Primary;
            set_cairo_color(cc, clickedcolor);
            cairo_set_line_width(cc, 0.1);

            round_rect(cc, x(), y(), w(), h(), 2);

            cairo_fill(cc);
            break;
        case Text:
            break;
    }

    if (Type != Primary && hovered && clicked) {
        textcolor = fl_darker(textcolor);
    }

    set_cairo_color(cc, textcolor);

    auto font = cairo_toy_font_face_create("Roboto", cairo_font_slant_t::CAIRO_FONT_SLANT_NORMAL,
                                           cairo_font_weight_t::CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_line_width(cc, 1);
    cairo_set_font_face(cc, font);
    cairo_set_font_size(cc, 12);

    cairo_text_extents_t extents;
    cairo_text_extents(cc, label(), &extents);
    cairo_move_to(cc, x() + w() / 2 - extents.width / 2, y() + h() / 2 + extents.height / 2);

    cairo_show_text(cc, label());
}

#include "ctype.h"

void Button::label(const char *l) {
    char *ll = (char *) strdup(l);
    for (int i = 0; i < strlen(l); ++i) {
        ll[i] = toupper(ll[i]);
    }
    Fl_Button::label(ll);
}

const char *Button::label() {
    return Fl_Button::label();
}
