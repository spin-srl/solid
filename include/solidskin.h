#pragma once

#include <Fl/Fl.H>
#include <pthread.h>
#include <cstdint>

[[noreturn]] void *skin_animation_handler(void *arg);

class Animation {
public:
    //Using system ticks
    uint64_t timestamp;

    //Measured in msecs
    uint64_t duration;
};

class SolidSkin {
public:
    static pthread_t animationthread;
    static SolidSkin *current;

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

    static bool initialize() {
        if (initialized)
            return false;

        current = new SolidSkin();
        Fl::set_font(0, "Roboto");
        Fl::set_font(1, "Roboto Bold");

        pthread_create(&animationthread, nullptr, skin_animation_handler, nullptr);

        initialized = true;

        return true;
    }
};
