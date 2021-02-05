#include "solidbase.h"
#include "window.h"
#include "button.h"
#include "box.h"
#include <Fl/Fl_Input.H>

using namespace Solid;

int main() {
    SolidBase::initialize();

    auto *mw = new Window(0, 0, 800, 400, "TestWindow", "TW");
    mw->end();

    Box *horizontalGroup = new Box(100, 10, 150, 50, "horizontalGroup");
    horizontalGroup->end();

    horizontalGroup->direction = Horizontal;

    auto b = new Button(0, 0, 0, 0, "Text", "TextB");
    auto b2 = new Button(0, 0, 0, 0, "Outline", "OutlineB");
    auto secondGroup = new Box(0, 0, 0, 0, "g0");
//    auto flInputTest = new Fl_Input(0, 0, 100, 25, "");

    secondGroup->direction = Vertical;

    b->boxAlign = BoxAlign::Fill;

    auto b3 = new Button(0, 0, 0, 0, "B3", "b3");
    auto b4 = new Button(0, 0, 0, 0, "B4", "b4");
    auto b5 = new Button(0, 0, 0, 0, "B5", "b5");
    b3->boxAlign = BoxAlign::Fill;
    b5->Type = Primary;

    b->Type = ButtonType::Text;
    b2->Type = ButtonType::Outline;
    b3->Type = ButtonType::Primary;

    horizontalGroup->position(5, 5);
    horizontalGroup->margin = Margins{5, 5, 5, 5};
    horizontalGroup->spacing = 5;

    horizontalGroup->add(b);
    horizontalGroup->add(b2);
    horizontalGroup->add(secondGroup);
    secondGroup->add(b3);
    secondGroup->add(b4);
    secondGroup->add(b5);
    secondGroup->spacing = 5;
    secondGroup->margin = Margins{0, 0, 0, 0};
//    horizontalGroup->add(flInputTest);

    mw->add(horizontalGroup);
    mw->resizable(horizontalGroup);
    mw->show();

    Fl::run();

    delete mw;
    return 0;
}
