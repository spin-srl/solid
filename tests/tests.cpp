#include <stdio.h>

#include "solidbase.h"
#include "window.h"
#include "group.h"
#include "button.h"

int main()
{
    SolidBase::initialize();

    Window* mw = new Window(0, 0, 1100, 100, "TestWindow", "TW");
    Group* g = new Group(5, 5, 80, 20, "", "group0");
    Button* b = new Button(5, 5, 80, 20, "TextButton", "TB");
    Button* b2 = new Button(5, 30, 80, 20, "OutlineButton", "TB");
    Button* b3 = new Button(5, 55, 80, 20, "PrimaryButton", "TB");

    b->Type = ButtonType::Text;
    b2->Type = ButtonType::Outline;
    b3->Type = ButtonType::Primary;

    mw->show();
    mw->add(g);
    g->add(b);

    SolidBase* bq = mw->GetChild("group0/TB");
    printf("B2 is %s\n", bq ? bq->Name : "Unknown");
    printf("b2's path: '%s'\n", bq->Path());

    Fl::run();

    delete mw;
    return 0;
}
