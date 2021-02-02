#include <group.h>
#include "solidbase.h"

class Box : public Group {
public:
    Box(int x, int y, int w, int h, const char *name);

    Measure layout() override;
    void draw();
    int handle(int evt);

    void resize(int x,int y,int w,int h) override;

};

