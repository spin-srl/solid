#include "widget.h"

using namespace Solid;

Widget::Widget(int x, int y, int w, int h, const char* label, const char* name):
    SolidBase(name),
    Fl_Widget(x, y, w, h, label)
{
    this->Name = name;
}
