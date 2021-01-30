#include "button.h"
#include "Fl/fl_draw.H"
#include <Fl/Fl_Group.H>

Button::Button(int x, int y, int w, int h, const char* l, const char* name):
    SolidBase(name),
    Fl_Button(x, y, w, h, l)
{
    this->labelfont(1);
    this->labelsize(12);
    this->label(l);
}

int Button::handle(int evt)
{
    switch (evt)
    {
    case FL_PUSH:
    case FL_RELEASE:
    case FL_LEAVE:
    case FL_ENTER:
        fl_cursor(Fl::belowmouse() == this ? FL_CURSOR_HAND : FL_CURSOR_ARROW);
        redraw();
        break;
    }

    return Fl_Button::handle(evt);
}

void Button::draw()
{
    fl_push_clip(x(),y(),w(),h());
    fl_rectf(x(), y(), w(), h(), SolidSkin::current->Surface);

    bool hovered = Fl::belowmouse() == this;
    bool clicked = Fl::event_button1();

    Fl_Color textcolor = hovered ? fl_lighter(SolidSkin::current->Primary) : SolidSkin::current->Primary;

    switch (Type)
    {
    case Outline:
        Fl_Color outlinecolor;
        Fl_Color target;

        outlinecolor = SolidSkin::current->Surface;
        target = fl_contrast(FL_WHITE, SolidSkin::current->Surface);

        outlinecolor = fl_color_average(outlinecolor, target, 0.8);
        fl_rect(x(), y(), w(), h(), outlinecolor);
        break;

    case Primary:
        textcolor = hovered ? fl_lighter(SolidSkin::current->OnPrimary) : SolidSkin::current->OnPrimary;
        Fl_Color clickedcolor;
        clickedcolor = clicked ? fl_darker(SolidSkin::current->Primary) : fl_lighter(SolidSkin::current->Primary);
        fl_rectf(x(), y(), w(), h(), hovered ? clickedcolor : SolidSkin::current->Primary);
        break;
    }

    if (Type != Primary && clicked)
    {
        textcolor = fl_darker(textcolor);
    }

    fl_color(textcolor);
    fl_font(labelfont(), labelsize());
    fl_draw(label(), x(), y(), w(), h(), align(), active() ? image() : deimage(), true);
   fl_pop_clip();
}
#include "ctype.h"

void Button::label(const char *l) {
    char* ll=(char*)strdup(l);
    for (int i = 0; i < strlen(l); ++i) {
        ll[i]=toupper(ll[i]);
    }
    Fl_Button::label(ll);
}

const char *Button::label() {
    return Fl_Button::label();
}
