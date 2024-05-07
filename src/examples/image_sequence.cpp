#include "examples.h"
#include "frame_data.h"

uint8_t r, g, b;
uint16_t pixel_data;
uint8_t frame = 0;

void setupImageSequence(VirtualMatrixPanel *virtualDisp)
{
}

void loopImageSequence(VirtualMatrixPanel *virtualDisp)
{
    for (int y = 0; y <= 63; y++)
    {
        for (int x = 0; x <= 63; x++)
        {
            pixel_data = color_array[pixel_array[frame * 64 * 64 + y * 64 + x]];
            // extract channels from 16-bit color in 5-6-5 format
            r = (pixel_data & 0xF800) >> 8;
            g = (pixel_data & 0x07E0) >> 3;
            b = (pixel_data & 0x001F) << 3;
            virtualDisp->drawPixel(x, y, virtualDisp->color565(r, g, b));
        }
    }
    frame = (frame + 1) % frame_count;
    delay(33);
    virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));
}