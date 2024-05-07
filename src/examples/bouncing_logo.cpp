#include <stdio.h>
#include "esp_config.h"
#include "examples.h"

struct rgb24
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

rgb24 hue2rgb(uint8_t hue)
{ // saturation and value are fixed at 255
    rgb24 rgb;
    uint8_t h = hue;
    uint8_t i = h / 43;             // i is the sector 0..5 around the color wheel
    uint8_t p = (h - (i * 43)) * 6; // p is the position in sector
    uint8_t q = 255 - p;            // q is the opposite percentage of p
    switch (i)
    {
    case 0:
        rgb.r = 255;
        rgb.g = p;
        rgb.b = 0;
        break;
    case 1:
        rgb.r = q;
        rgb.g = 255;
        rgb.b = 0;
        break;
    case 2:
        rgb.r = 0;
        rgb.g = 255;
        rgb.b = p;
        break;
    case 3:
        rgb.r = 0;
        rgb.g = q;
        rgb.b = 255;
        break;
    case 4:
        rgb.r = p;
        rgb.g = 0;
        rgb.b = 255;
        break;
    case 5:
        rgb.r = 255;
        rgb.g = 0;
        rgb.b = q;
        break;
    }
    return rgb;
}

const int rectWidth = 16;
const int rectHeight = 10;

const int SCREEN_WIDTH = PANEL_RES_X * NUM_COLS;
const int SCREEN_HEIGHT = PANEL_RES_Y * NUM_ROWS;

int x = 6;
int y = 0;
int directionX = 1;
int directionY = 1;

rgb24 color = hue2rgb(0);

void setupBouncingLogo(VirtualMatrixPanel *virtualDisp) {}

void loopBouncingLogo(VirtualMatrixPanel *virtualDisp)
{
    // draw rect
    virtualDisp->fillRect(x, y, rectWidth, rectHeight, virtualDisp->color565(color.r, color.g, color.b));

    // move rect diagonally
    x += directionX;
    y += directionY;

    // change direction if we hit the edge
    if (x == SCREEN_WIDTH - rectWidth || x == 0)
    {
        directionX *= -1;
        color = hue2rgb(random(0, 255));
    }
    if (y == SCREEN_HEIGHT - rectHeight || y == 0)
    {
        directionY *= -1;
        color = hue2rgb(random(0, 255));
    }

    // delays
    delay(10);
    virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));
}