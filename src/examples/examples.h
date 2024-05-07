#pragma once
#include "ESP32-VirtualMatrixPanel-I2S-DMA.h"
#include <FastLED.h>

enum ExampleType
{
    HELLO_WORLD,
    RAINBOW,
    IMAGE_SEQUENCE,
    BOUNCING_LOGO
};

void setupHelloWorld(MatrixPanel_I2S_DMA *dma_display);
void loopHelloWorld(MatrixPanel_I2S_DMA *dma_display);

void setupRainbow(VirtualMatrixPanel *virtualDisp, MatrixPanel_I2S_DMA *dma_display);
void loopRainbow(VirtualMatrixPanel *virtualDisp, MatrixPanel_I2S_DMA *dma_display);

void setupImageSequence(VirtualMatrixPanel *virtualDisp);
void loopImageSequence(VirtualMatrixPanel *virtualDisp);

void setupBouncingLogo(VirtualMatrixPanel *virtualDisp);
void loopBouncingLogo(VirtualMatrixPanel *virtualDisp);