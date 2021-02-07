//
// Created by ddt on 2/7/21.
//

#ifndef SOLID_CHECKBOX_H
#define SOLID_CHECKBOX_H

#include "solidbase.h"
#include <Fl/Fl_Check_Button.H>

namespace Solid {
    class CheckBox : public SolidBase, public Fl_Check_Button {
    public:
        CheckBox(int x, int y, int w, int h, const char *label, const char *name) : Fl_Check_Button(x, y, w, h, label),
                                                                                    SolidBase(name) {
        }
    };
}

#endif //SOLID_CHECKBOX_H
