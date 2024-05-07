#include "examples.h"
#include "esp_config.h"

uint16_t time_counter = 0, cycles = 0, fps = 0;
unsigned long fps_timer;
CRGB currentColor;
CRGBPalette16 palettes[] = {HeatColors_p, LavaColors_p, RainbowColors_p, RainbowStripeColors_p, CloudColors_p};
CRGBPalette16 currentPalette = palettes[0];

CRGB ColorFromCurrentPalette(uint8_t index = 0, uint8_t brightness = 255, TBlendType blendType = LINEARBLEND)
{
    return ColorFromPalette(currentPalette, index, brightness, blendType);
}

void setupRainbow(VirtualMatrixPanel *virtualDisp, MatrixPanel_I2S_DMA *dma_display)
{
}

void loopRainbow(VirtualMatrixPanel *virtualDisp, MatrixPanel_I2S_DMA *dma_display)
{
    dma_display->setBrightness8(100);

    for (int x = 0; x < PANEL_RES_X * NUM_COLS; x++)
    {
        for (int y = 0; y < PANEL_RES_Y * NUM_ROWS; y++)
        {
            int16_t v = 0;
            uint8_t wibble = sin8(time_counter);
            v += sin16(x * wibble * 3 + time_counter);
            v += cos16(y * (128 - wibble) + time_counter);
            v += sin16(y * x * cos8(-time_counter) / 8);

            currentColor = ColorFromPalette(currentPalette, (v >> 8) + 127); //, brightness, currentBlendType);
            virtualDisp->drawPixelRGB888(x, y, currentColor.r, currentColor.g, currentColor.b);
        }
    }

    ++time_counter;
    ++cycles;
    ++fps;

    if (cycles >= 256)
    {
        time_counter = 0;
        cycles = 0;
        currentPalette = palettes[random(0, sizeof(palettes) / sizeof(palettes[0]))];
    }
    if (fps_timer + 5000 < millis())
    {
        Serial.printf_P(PSTR("Effect fps: %d\n"), fps / 5);
        fps_timer = millis();
        fps = 0;
    }
}