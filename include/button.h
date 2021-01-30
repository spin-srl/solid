#pragma once

#include <Fl/Fl_Button.H>
#include "solidbase.h"

enum ButtonType
{
        Text,
        Outline,
        Primary
};

class Button: public SolidBase, public Fl_Button
{
  public:
        ButtonType Type = Text;

        Button(int x, int y, int w, int h, const char* label = nullptr, const char* name = nullptr);

        int handle(int evt);

        void draw();
};
