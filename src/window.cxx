#include "window.h"

Window::Window(int x, int y, int w, int h, const char* label, const char* name):
    Fl_Double_Window(x, y, w, h, label),
    SolidBase(name)
{
    color(SolidSkin::current->Surface);
}
