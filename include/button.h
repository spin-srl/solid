#pragma once

#include <Fl/Fl_Button.H>
#include <Fl/Fl_Menu_.H>
#include "solidbase.h"

namespace Solid {

    enum ButtonType {
        Text,
        Outline,
        Primary
    };

    class Button : public SolidBase, public Fl_Button {
    public:
        ButtonType Type = ButtonType::Text;

        Button(int x, int y, int w, int h, const char *label = nullptr, const char *name = nullptr);
        int handle(int evt) override;

        virtual void label(const char *l);

        const char *label();

        Measure layout();

        Fl_Color buttonColor();

        Fl_Color outlineColor();

        Fl_Color textColor();

        void draw() override;

        static Button *Primary(int x, int y, int w, int h, const char *label = nullptr, const char *name = nullptr);

        static Button *Outline(int x, int y, int w, int h, const char *label, const char *name= nullptr);

        static Button *Text(int x, int y, int w, int h, const char *label, const char *name= nullptr);
    };

    static const double degree_to_radian = 3.14159265358979 / 180.0;

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
}
