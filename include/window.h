#pragma once

#include <Fl/Fl_Double_Window.H>
#include "solidbase.h"

namespace Solid {
    class Window : public SolidBase, virtual public Fl_Double_Window {
    public:
        Window(int x, int y, int w, int h, const char *label = nullptr, const char *name = nullptr);

        Measure layout() override;

        void draw() override;

        void resize(int x, int y, int w, int h) override;

        char *Path() override;

        void updateLayout() const;

        cairo_t *cc;

        void show() override;
    };
}

