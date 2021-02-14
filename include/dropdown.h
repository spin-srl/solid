//
// Created by ddt on 2/6/21.
//

#ifndef SOLID_DROPDOWN_H
#define SOLID_DROPDOWN_H

#include <Fl/Fl_Double_Window.H>
#include <Fl/Fl_Menu_.H>
#include "button.h"

namespace Solid {
class DropDown: public Solid::Button{
    public:
        int selectedIndex = -1;
        std::vector<char *> *Options;

        DropDown(int x, int y, int w, int h, const char *label= nullptr, const char *name= nullptr);

        void draw() override;

        Measure layout();

    };
}

#endif //SOLID_DROPDOWN_H
