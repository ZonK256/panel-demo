#include <stdio.h>
#include "examples.h"

void drawText(int colorWheelOffset, MatrixPanel_I2S_DMA *dma_display);
uint16_t colorWheel(uint8_t pos, MatrixPanel_I2S_DMA *dma_display);
uint8_t wheelval = 0;

void setupHelloWorld(MatrixPanel_I2S_DMA *dma_display)
{
    dma_display->fillRect(0, 0, dma_display->width(), dma_display->height(), dma_display->color444(0, 15, 0));
    delay(500);

    // draw a box in yellow
    dma_display->drawRect(0, 0, dma_display->width(), dma_display->height(), dma_display->color444(15, 15, 0));
    delay(500);

    // draw an 'X' in red
    dma_display->drawLine(0, 0, dma_display->width() - 1, dma_display->height() - 1, dma_display->color444(15, 0, 0));
    dma_display->drawLine(dma_display->width() - 1, 0, 0, dma_display->height() - 1, dma_display->color444(15, 0, 0));
    delay(500);

    // draw a blue circle
    dma_display->drawCircle(10, 10, 10, dma_display->color444(0, 0, 15));
    delay(500);

    // fill a violet circle
    dma_display->fillCircle(40, 21, 10, dma_display->color444(15, 0, 15));
    delay(500);

    // fill the screen with 'black'
    dma_display->fillScreen(dma_display->color444(0, 0, 0));
}

void loopHelloWorld(MatrixPanel_I2S_DMA *dma_display)
{
    drawText(wheelval, dma_display);
    wheelval += 1;

    delay(20);
}

void drawText(int colorWheelOffset, MatrixPanel_I2S_DMA *dma_display)
{
    dma_display->setTextSize(1);     // size 1 == 8 pixels high
    dma_display->setTextWrap(false); // Don't wrap at end of line - will do ourselves

    dma_display->setCursor(5, 0); // start at top left, with 8 pixel of spacing
    uint8_t w = 0;
    const char *str = "ESP32 DMA";
    for (w = 0; w < strlen(str); w++)
    {
        dma_display->setTextColor(colorWheel((w * 32) + colorWheelOffset, dma_display));
        dma_display->print(str[w]);
    }

    dma_display->println();
    dma_display->print(" ");
    for (w = 9; w < 18; w++)
    {
        dma_display->setTextColor(colorWheel((w * 32) + colorWheelOffset, dma_display));
        dma_display->print("*");
    }

    dma_display->println();

    dma_display->setTextColor(dma_display->color444(15, 15, 15));
    dma_display->println("XDDDDDDDDDDD");

    // print each letter with a fixed rainbow color
    dma_display->setTextColor(dma_display->color444(0, 8, 15));
    dma_display->print('3');
    dma_display->setTextColor(dma_display->color444(15, 4, 0));
    dma_display->print('2');
    dma_display->setTextColor(dma_display->color444(15, 15, 0));
    dma_display->print('x');
    dma_display->setTextColor(dma_display->color444(8, 15, 0));
    dma_display->print('6');
    dma_display->setTextColor(dma_display->color444(8, 0, 15));
    dma_display->print('4');

    // Jump a half character
    dma_display->setCursor(34, 24);
    dma_display->setTextColor(dma_display->color444(0, 15, 15));
    dma_display->print("*");
    dma_display->setTextColor(dma_display->color444(15, 0, 0));
    dma_display->print('R');
    dma_display->setTextColor(dma_display->color444(0, 15, 0));
    dma_display->print('G');
    dma_display->setTextColor(dma_display->color444(0, 0, 15));
    dma_display->print("B");
    dma_display->setTextColor(dma_display->color444(15, 0, 8));
    dma_display->println("*");
}

uint16_t colorWheel(uint8_t pos, MatrixPanel_I2S_DMA *dma_display)
{
    if (pos < 85)
    {
        return dma_display->color565(pos * 3, 255 - pos * 3, 0);
    }
    else if (pos < 170)
    {
        pos -= 85;
        return dma_display->color565(255 - pos * 3, 0, pos * 3);
    }
    else
    {
        pos -= 170;
        return dma_display->color565(0, pos * 3, 255 - pos * 3);
    }
}