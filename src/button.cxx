#include "button.h"
#include "Fl/fl_draw.H"
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Cairo.H>
#include <cairo.h>

using namespace Solid;

Button::Button(int x, int y, int w, int h, const char *label, const char *name) :
        SolidBase(name),
        Fl_Button(x, y, w, h, label) {
    this->labelfont(1);
    this->labelsize(12);
    this->label(label);
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

    auto font = SolidSkin::fonts[1];

    cairo_set_line_width(cc, 1);
    cairo_set_font_face(cc, font);
    cairo_set_font_size(cc, labelsize());

    cairo_text_extents_t extents;
    cairo_text_extents(cc, label(), &extents);
    cairo_move_to(cc, x() + w() / 2 - extents.width / 2, y() + h() / 2 + extents.height / 2);

    cairo_show_text(cc, label());

    if (Fl::belowmouse() != this->as_widget())
        return;

    debugDraw();
}

#include "ctype.h"

void Button::label(const char *l) {
    if (l == nullptr)return;

    char *ll = (char *) strdup(l);
    for (int i = 0; i < strlen(l); ++i) {
        ll[i] = toupper(ll[i]);
    }
    Fl_Button::label(ll);
}

const char *Button::label() {
    return Fl_Button::label();
}

Measure Button::layout() {
    cairo_text_extents_t extents;

    auto cc = Fl::cairo_cc();
    if (cc == nullptr || label() == nullptr) {
        printf("NOT Found!\n");
        return Measure{w(), h()};
    }

    cairo_set_font_face(cc, SolidSkin::fonts[1]);
    cairo_set_font_size(cc, labelsize());
    cairo_text_extents(cc, label(), &extents);

    return Measure{20 + static_cast<int>(extents.width + padding.Horizontal()),
                   15 + static_cast<int>(extents.height + padding.Vertical())};
}
