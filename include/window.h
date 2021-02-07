#pragma once

#include <Fl/Fl_Double_Window.H>
#include "solidbase.h"
#include "box.h"

namespace Solid {
    class Window : public SolidBase, virtual public Fl_Double_Window {
        Group *Content;
        Group *TitleBar;

        static cairo_font_face_t *TitleFont;
        ///This is used to keep track of the dragging and resizing functionalities
        int xoff, yoff;

        cairo_surface_t *surf;
        cairo_t* scc;
        Fl_RGB_Image *windowShapeImage;

    public:
        Window(int x, int y, int w, int h, const char *label = nullptr, const char *name = nullptr);

        int titleHeight = 30;

        Measure layout() override;

        enum DragType {
            None = 0,
            Move = 1 << 0,
            ResizeWidth = 1 << 1,
            ResizeHeight = 1 << 2
        } Drag = None;

        virtual void add(Fl_Widget *w);

        void draw() override;

        void resize(int x, int y, int w, int h) override;

        char *Path() override;

        void updateLayout() const;

        Fl_Widget *resizable();

        virtual void resizable(Fl_Widget *w);

        cairo_t *cc;

        void show() override;

        int handle(int evt);

        virtual int h();

        virtual int w();
    };
}
