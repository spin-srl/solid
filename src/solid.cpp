#include "solid.h"
#include <stdio.h>

#include <assert.h>

// int SolidWidget::children() {
//     printf("This shouldn't be being called!\n");
//     return 0;
// }

// Widget* SolidWidget::GetChild(const char* name) {
//     printf("This shouldn't be being called!\n");
//     return nullptr;
// }

// Widget* SolidWidget::FindChild(const char* name) {
//     printf("This shouldn't be being called!\n");
//     return nullptr;
// }

// inline Widget* SolidWidget::child(int index) {
//     printf("This shouldn't be being called!\n");
//     return nullptr;
// }

int main()
{
    Window* mw = new Window(0, 0, 1100, 100, "TestWindow", "TW");
    Group* g=new Group(5,5,80,20,"","group0");
    Button* b = new Button(5, 5, 80, 20, "TestButton", "TB");

    mw->show();
    mw->add(g);
    g->add(b);

    SolidBase* b2 = mw->GetChild("group0/TB");
    printf("B2 is %s\n", b2 ? b2->Name : "Unknown");
    printf("b2's path: '%s'\n",b2->Path());

    Fl::run();

    delete mw;
    return 0;
}
