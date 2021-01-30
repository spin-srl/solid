#pragma once

#include <Fl/Fl_Widget.H>
#include "solidbase.h"

class Widget: public SolidBase, public Fl_Widget
{
  public:
        Widget(int x, int y, int w, int h, const char* label = nullptr, const char* name = nullptr);
};
