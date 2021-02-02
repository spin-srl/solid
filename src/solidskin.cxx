#include "solidskin.h"
#include "unistd.h"

bool SolidSkin::initialized = false;
SolidSkin *SolidSkin::current;
pthread_t SolidSkin::animationThread;
std::vector<cairo_font_face_t *> SolidSkin::fonts = {cairo_toy_font_face_create("Roboto",
                                                                                cairo_font_slant_t::CAIRO_FONT_SLANT_NORMAL,
                                                                                cairo_font_weight_t::CAIRO_FONT_WEIGHT_NORMAL),
                                                     cairo_toy_font_face_create("Roboto",
                                                                                cairo_font_slant_t::CAIRO_FONT_SLANT_NORMAL,
                                                                                cairo_font_weight_t::CAIRO_FONT_WEIGHT_BOLD)};

bool SolidSkin::initialize() {
    if (initialized)
        return false;

    current = new SolidSkin();

//    pthread_create(&animationThread, nullptr, skin_animation_handler, nullptr);

    initialized = true;

    return true;
}


[[noreturn]] void *skin_animation_handler(void *arg) {
    while (true) {
        printf("Animating!\n");
        sleep(1);
    }
}
