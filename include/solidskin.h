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

        static void toggleMode() {
            //TODO: Store current DARK/LIGHT mode in some kind of preferences
            static bool darkMode = true;

            if (darkMode) {
                current->Primary = fl_rgb_color(0x2a, 0x4c, 0xf8);
                current->OnPrimary = FL_BLACK;

                current->Secondary = fl_rgb_color(0xf8, 0x70, 0x2a);
                current->OnSecondary = FL_BLACK;

                current->Surface = FL_BLACK;
                current->OnSurface = FL_WHITE;
            } else {
                current->Primary = fl_rgb_color(0x2a, 0x4c, 0xf8);
                current->OnPrimary = FL_WHITE;

                current->Secondary = fl_rgb_color(0xf8, 0x70, 0x2a);
                current->OnSecondary = FL_WHITE;

                current->Surface = FL_WHITE;
                current->OnSurface = FL_BLACK;
            }
            darkMode = !darkMode;
        }

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
