#pragma once

#include <Fl/Fl.H>
#include <Fl/Fl_Widget.H>
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <cairo.h>
#include <cassert>

#include "solidskin.h"

/// This enum holds the Align options for every widget
enum BoxAlign {
    Start,
    End,
    Center,
    Fill
};

/// Used to return calculated sizes
struct Measure {
    double Width, Height;

    Measure() {
        Width = 0;
        Height = 0;
    }

    /// Construct from ints
    Measure(int w, int h) : Width(w), Height(h) {
    };
};

///Margins of the widget
struct Margins {
    double top, bottom, left, right;

    inline double Vertical() const {
        return top + bottom;
    }

    inline double Horizontal() const {
        return left + right;
    }
};

///Padding of the widget
struct Padding {
    double top, bottom, left, right;

    inline double Vertical() const {
        return top + bottom;
    }

    inline double Horizontal() const {
        return left + right;
    }
};

///Holds which direction will the box layout follow
enum Direction {
    Horizontal,
    Vertical
};

///Base of every Solid-Widget
class SolidBase {
public:
    ///Name of the widget, used for runtime widget identification
    const char *Name;

    ///Assignable destroy callback
    void (*onDestroy)(SolidBase *w);

    SolidBase(const char *name);

    virtual ~SolidBase();

    //TODO: Finish `char *Path()`, check the effect of non-named widgets
    //TODO: Relative paths(like using .. and .) and path wildcards
    ///Gets the path of the widget
    virtual char *Path();

    ///Splits the path and returns whether there are more path-items left to process or it was the last
    ///params:
    /// path: the path to process
    /// cname: returns the current path name to process
    /// more: returns the remaining path
    ///returns: true if there is more
    static bool get_next_child(char *path, char **cname, char **more);

    ///Static flag to signal the initialized status of the library
    static bool initialized;

    ///Library Setup
    static bool initialize();

    ///Dynamic cast to Fl_Widget*
    Fl_Widget *as_widget();

    ///Puts this widget into `w`, with a margin of 5 units
    void fitIn(Fl_Widget *w, int margin = 5);

    ///Returns a children using the given path
    virtual SolidBase *GetChild(const char *path);

    ///Just for debugging reasons
    ///Draws a red box around widgets and a label with it's name
    void debugDraw();

    ///Widget's properties for layout stuffs
    BoxAlign boxAlign = Center;
    Margins margin{};
    Padding padding{};
    Direction direction = Horizontal;
    double spacing = 0;

    ///refreshLayout stands for 'Should the library refresh the layout so the user doesn't have to move a finger'
    bool refreshLayout = true;

    ///By default this only returns the current width/height for this widget
    ///Subsequent implementations(overrides) of this method can take into account children widgets and
    ///their preferences, and return the target size instead of the current one
    virtual Measure layout();
};
