#pragma once

#include <Fl/Fl.H>
#include <Fl/Fl_Widget.H>
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>

#include "solidskin.h"

class SolidBase{
public:
    const char* Name;

    void (*onDestroy)(SolidBase* w);

    SolidBase(const char* name);

    virtual ~SolidBase();

    char* Path();

    static bool get_next_child(char* path, char** cname, char** more);
    static bool initialized;

    static bool initialize(){
        if (initialized)
            return false;

        SolidSkin::initialize();

        initialized=true;

        return true;
    }

//        "Group0/Group1/Widget"
    virtual SolidBase* GetChild(const char* path);

};
