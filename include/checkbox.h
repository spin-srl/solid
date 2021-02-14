//
// Created by ddt on 2/7/21.
//

#ifndef SOLID_CHECKBOX_H
#define SOLID_CHECKBOX_H

#include "solidbase.h"
#include "button.h"
#include <FL/Fl_Check_Button.H>

namespace Solid {
    class CheckBox : public Button {
    public:
        CheckBox(int x, int y, int w, int h, const char *label= nullptr, const char *name = nullptr);

        void draw();

        Measure layout() override;

        void label(const char *label) override;

        const char *label();;
    };
}

#endif //SOLID_CHECKBOX_H
