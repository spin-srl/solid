#include "solidbase.h"
#include "window.h"
#include "button.h"
#include "box.h"
#include <Fl/Fl_Input.H>

using namespace Solid;

int main() {
    SolidBase::initialize();

    auto *mw = new Fl_Window(0, 0, 800, 400, "TestWindow");
    mw->end();

    auto container = new Group(0, 0, mw->w(), mw->h());
    auto box = new Box(0, 0, mw->w(), mw->h(), "box0");

    auto anotherBox = new Box(0, 0, 0, 0, "anotherBox");
    anotherBox->direction = Vertical;
    anotherBox->add(Button::Primary(0, 0, 100, 100, "Test_0", "qb"));
    anotherBox->add(Button::Outline(0, 0, 100, 100, "Test_1", "qb"));
    anotherBox->add(Button::Text(0, 0, 100, 100, "Test_2", "qb"));
    anotherBox->add(Button::Primary(0, 0, 100, 100, "Test_0", "qb"));
    Button *o = Button::Outline(0, 0, 100, 100, "Test_1", "qb");
    anotherBox->add(o);
    o->Expand=true;
    anotherBox->add(Button::Text(0, 0, 100, 100, "Test_2", "qb"));
    anotherBox->add(Button::Primary(0, 0, 100, 100, "Test_0", "qb"));
    anotherBox->add(Button::Outline(0, 0, 100, 100, "Test_1", "qb"));
    anotherBox->add(Button::Text(0, 0, 100, 100, "Test_2", "qb"));

    box->add(Button::Primary(0, 0, 100, 100, "Test_0", "qb"));
    Button *pButton = Button::Primary(0, 0, 100, 100, "Test_1", "qb");
    pButton->Expand=true;
    box->add(pButton);
    Button *qButton = Button::Primary(0, 0, 100, 100, "Test_1", "qb");
    qButton->Expand=true;
    box->add(qButton);
    Button *rButton = Button::Primary(0, 0, 100, 100, "Test_1", "qb");
    rButton->Expand=true;
    box->add(rButton);
    box->add(Button::Text(0, 0, 100, 100, "Test_2", "qb"));
    box->add(anotherBox);

    container->add(box);
    box->box(FL_FLAT_BOX);
    box->color(FL_RED);
    box->resizable(anotherBox);
    container->resizable(box);

    container->box(Fl_Boxtype::FL_FLAT_BOX);
    container->color(FL_GRAY);

    mw->add(container);
    mw->resizable(container);
    mw->show();

    Fl::run();

    delete mw;
    return 0;
}
