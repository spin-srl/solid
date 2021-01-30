#pragma once

#include "Fl/Fl.H"

class SolidSkin
{
  public:
        static SolidSkin current;

//    Fl_Color Primary=fl_rgb_color(0x2a,0x4c,0xf8);
//    Fl_Color OnPrimary=FL_BLACK;

//    Fl_Color Secondary=fl_rgb_color(0xf8,0x70,0x2a);
//    Fl_Color OnSecondary=FL_BLACK;

//    Fl_Color Surface=FL_BLACK;
//    Fl_Color OnSurface=FL_WHITE;

        Fl_Color Primary = fl_rgb_color(0x2a, 0x4c, 0xf8);
        Fl_Color OnPrimary = FL_WHITE;

        Fl_Color Secondary = fl_rgb_color(0xf8, 0x70, 0x2a);
        Fl_Color OnSecondary = FL_WHITE;

        Fl_Color Surface = FL_WHITE;
        Fl_Color OnSurface = FL_BLACK;
};
