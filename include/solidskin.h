#pragma once

#include <Fl/Fl.H>
#include <pthread.h>
#include <cstdint>
#include <vector>
namespace Solid {


    class SolidSkin {
    public:
        static pthread_t animationThread;
        static SolidSkin *current;

        static std::vector<cairo_font_face_t *> fonts;

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

        static bool initialized;

        static bool initialize();
    };
}