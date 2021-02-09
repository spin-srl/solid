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


void Button::draw() {
    cairo_t *cc = get_cc();

//    cairo_rectangle(cc, parent()->x(), parent()->y(), parent()->w(), parent()->h());
//    cairo_clip(cc);

    cairo_rectangle(cc, x(), y(), w(), h());
    set_cairo_color(cc, SolidSkin::current->Surface);
    cairo_fill(cc);

    bool hovered = Fl::belowmouse() == this;
    bool clicked = Fl::event_button1();

    switch (Type) {
        case ButtonType::Outline:
            set_cairo_color(cc, outlineColor());
            cairo_set_line_width(cc, 0.6);
            round_rect(cc, x(), y(), w(), h(), 2);
            cairo_stroke(cc);
            break;

        case ButtonType::Primary:
            set_cairo_color(cc, buttonColor());
            cairo_set_line_width(cc, 0.1);

            round_rect(cc, x(), y(), w(), h(), 2);

            cairo_fill(cc);
            break;
        case ButtonType::Text:
            break;
    }

    set_cairo_color(cc, textColor());

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
#include "solidbase.h"

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
        return Measure{w(), h()};
    }

    cairo_set_font_face(cc, SolidSkin::fonts[1]);
    cairo_set_font_size(cc, labelsize());
    cairo_text_extents(cc, label(), &extents);

    return Measure{20 + static_cast<int>(extents.width + padding.Horizontal()),
                   15 + static_cast<int>(extents.height + padding.Vertical())};
}

Button *Button::Primary(int x, int y, int w, int h, const char *label, const char *name) {
    auto b = new Button(x, y, w, h, label, name);
    b->Type = ButtonType::Primary;
    return b;
}

Button *Button::Outline(int x, int y, int w, int h, const char *label, const char *name) {
    auto b = new Button(x, y, w, h, label, name);
    b->Type = ButtonType::Outline;
    return b;
}

Button *Button::Text(int x, int y, int w, int h, const char *label, const char *name) {
    auto b = new Button(x, y, w, h, label, name);
    b->Type = ButtonType::Text;
    return b;
}

Fl_Color Button::buttonColor() {
    switch (Type) {
        case ButtonType::Text:
        case ButtonType::Outline:
            return SolidSkin::current->Surface;
        default:
            break;
    }

    bool hovered = Fl::belowmouse() == this;
    bool clicked = hovered && Fl::event_button1();

    if (!active()) {
        hovered = false;
        clicked = false;
    }

    Fl_Color ret = clicked ? fl_darker(SolidSkin::current->Primary) : fl_lighter(SolidSkin::current->Primary);
    ret = hovered ? ret : SolidSkin::current->Primary;

    if (!active()) {
        uchar r, g, b;

        Fl::get_color(ret, r, g, b);

        float sum = r + g + b;
        ret = fl_gray_ramp(sum / 3.0);
    }

    return ret;
}

Fl_Color Button::outlineColor() {
    auto ret = SolidSkin::current->Surface;
    Fl_Color target;

    ret = SolidSkin::current->Surface;
    target = fl_contrast(FL_WHITE, SolidSkin::current->Surface);

    ret = fl_color_average(ret, target, 0.8);

    return ret;
}

Fl_Color Button::textColor() {
    Fl_Color ret;
    bool hovered = Fl::belowmouse() == this;
    bool clicked = hovered && Fl::event_button1();

    if (!active()) {
        hovered = false;
        clicked = false;
    }

    if (Type == ButtonType::Primary) {
        ret = hovered ? fl_lighter(SolidSkin::current->OnPrimary)
                      : SolidSkin::current->OnPrimary;
    } else {
        ret = hovered ? fl_lighter(SolidSkin::current->Primary)
                      : SolidSkin::current->Primary;
    }
    if (Type != ButtonType::Primary && hovered && clicked) {
        ret = fl_darker(ret);
    }

    if (!active()) {
        uchar r, g, b;

        Fl::get_color(ret, r, g, b);

        float sum = r + g + b;
        ret = fl_gray_ramp(sum / 3.0);
    }

    return ret;
}
