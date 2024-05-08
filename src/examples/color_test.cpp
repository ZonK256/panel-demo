#include "examples.h"
#include "esp_config.h"

void setupColorTest(VirtualMatrixPanel *virtualDisp)
{
    virtualDisp->fillRect(0, 0, virtualDisp->width(), virtualDisp->height(), virtualDisp->color444(255, 255, 255));
}

void loopColorTest(VirtualMatrixPanel *virtualDisp)
{
}