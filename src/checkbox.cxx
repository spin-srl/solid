#include "checkbox.h"

Solid::CheckBox::CheckBox(int x, int y, int w, int h, const char *label, const char *name) : Button(x, y, w, h, label,
                                                                                                    name) {
    Fl_Button::label(label);
    Type = ButtonType::Text;

    callback([](Fl_Widget *w, void *arg) {
        CheckBox *c = dynamic_cast<CheckBox *>(w);
        c->value(!c->value());
    });
}

void Solid::CheckBox::draw() {
    auto cc = get_cc();
    cairo_text_extents_t extents;

    set_cairo_color(cc, SolidSkin::current->OnSurface);
    cairo_set_font_size(cc, 12);
    cairo_set_font_face(cc, SolidSkin::fonts[1]);
    cairo_text_extents(cc, label(), &extents);

    cairo_move_to(cc, x() + 25, y() + h() / 2 + extents.height / 2);
    cairo_show_text(cc, label());

    set_cairo_color(cc, textColor());
    int q = 16;
    round_rect(cc, x() + 1, y() + h() / 2 - q / 2, q, q, 2);

    if (value()) {
        cairo_fill(cc);

#define GOTO_CENTER cairo_move_to(cc, x()+1+q/2, y()+h()/2+4);
        set_cairo_color(cc, SolidSkin::current->Surface);
        cairo_set_line_width(cc, 1);

        GOTO_CENTER
        cairo_rel_line_to(cc, -q / 4, -q / 4 + 0.5);
        cairo_stroke(cc);

        GOTO_CENTER
        cairo_rel_line_to(cc, q / 3, -q / 2 - 0.5);
        cairo_stroke(cc);
    } else
        cairo_stroke(cc);
}

Solid::Measure Solid::CheckBox::layout() {
    auto ret = Button::layout();
    ret.Width += 25;
    return ret;
}

void Solid::CheckBox::label(const char *label) {
    Fl_Button::label(label);
}

const char *Solid::CheckBox::label() { return Fl_Button::label(); }
