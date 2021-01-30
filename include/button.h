#pragma once

#include <Fl/Fl_Button.H>
#include "solidbase.h"

enum ButtonType {
    Text,
    Outline,
    Primary
};

class Button : public SolidBase, public Fl_Button {
public:
    ButtonType Type = Text;

    Button(int x, int y, int w, int h, const char *l = nullptr, const char *name = nullptr);

    int handle(int evt) override;

    void label(const char *l);

    const char *label();

    void draw() override;
};
