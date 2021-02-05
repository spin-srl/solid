#pragma once

#include <Fl/Fl_Group.H>
#include "solidbase.h"

namespace Solid {
    class Group : public SolidBase, public Fl_Group {
    public:
        Group(int x, int y, int w, int h, const char *label = nullptr, const char *name = nullptr);

        void resize(int x, int y, int w, int h);

        void draw();
    };
}