#pragma once

#include "group.h"
#include "solidbase.h"

namespace Solid {
    class Box : public Group {
    public:
        Box(int x, int y, int w, int h, const char *name= nullptr);

        virtual Measure layout() override;

        void resize(int x, int y, int w, int h) override;
        void draw();
    };
}
