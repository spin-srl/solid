#include "group.h"

Group::Group(int x, int y, int w, int h, const char* label, const char* name):
    SolidBase(name),
    Fl_Group(x, y, w, h, label)
{
    end();
}
