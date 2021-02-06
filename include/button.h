#pragma once

#include <Fl/Fl_Button.H>
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

        void label(const char *l);

        const char *label();

        Measure layout();

        void draw() override;

        static Button *Primary(int x, int y, int w, int h, const char *label = nullptr, const char *name = nullptr);

        static Button *Outline(int x, int y, int w, int h, const char *label, const char *name);

        static Button *Text(int x, int y, int w, int h, const char *label, const char *name);
    };
}
