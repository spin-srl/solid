#include "solidbase.h"
#include "window.h"
#include "button.h"
#include "../src/box.h"

int main() {
//    Fl::cairo_autolink_context(true);

    SolidBase::initialize();

    auto *mw = new Window(0, 0, 800, 400, "TestWindow", "TW");
    mw->end();

    Box *horizontalGroup = new Box(0, 0, 100, 100, "g0");
    horizontalGroup->end();

    horizontalGroup->direction = Horizontal;

    auto b = new Button(5, 5, 80, 20, "Text", "TextB");
    auto b2 = new Button(5, 30, 80, 20, "Outline", "OutlineB");
    auto b3 = new Button(5, 55, 80, 20, "Primary", "PrimaryB");
    auto g2 = new Box(0, 0, 0, 0, "VBox");

    b->boxAlign = BoxAlign::Fill;

    g2->padding = Padding{5, 5, 5, 5};
    g2->direction = Vertical;

    auto a3 = new Button(0, 0, 100, 20, "B", "b3");
    a3->boxAlign = BoxAlign::Fill;
    g2->add(new Button(0, 0, 100, 20, "Button 1", "b0"));
    g2->add(a3);
    g2->add(new Button(0, 0, 100, 20, "Button 1", "b1"));
    g2->add(new Button(0, 0, 100, 20, "Button 1", "b2"));

    b->Type = ButtonType::Text;
    b2->Type = ButtonType::Outline;
    b3->Type = ButtonType::Primary;

    horizontalGroup->position(5, 5);
    horizontalGroup->margin = Margins{5, 5, 5, 5};
    horizontalGroup->spacing = 5;

    horizontalGroup->add(b);
    horizontalGroup->add(g2);
    horizontalGroup->add(b2);
    horizontalGroup->add(b3);

    mw->add(horizontalGroup);

    mw->show();

    Fl::run();

    delete mw;
    return 0;
}
