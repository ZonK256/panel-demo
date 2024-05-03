// HUB75 PINOUT             IDC COLORS                              ESP32 PINOUT
// ___________________
// | 1 R0   | G0 2  |      | Bordowy        | Żółty          |        25 | 26
// | 3 B0   | GND 4 |      | Niebieski      | Pomaranczowy   |        27 | GND
// | 5 R1   | G1 6  |      | Zielony        | Czerwony       |        14 | 12
// | 7 B1   | GND 8 |      | Żółty          | Brązowy        |        13 | GND
// | 9 A    | B  10 |      | Pomaarańczowy  | Czarny         |        23 | 19
// | 11 C   | D  12 |      | Czerwony       | Biały          |        5  | 17
// | 13 CLK | LAT 14|      | Brązowy        | Szary          |        16 | 4
// | 15 OE  | GND 16|      | Czarny         | xxx            |        15 | GND
// -------------------

// #define _DEBUG_ // comment this line to disable debug output

// // debugging macros
// #ifdef _DEBUG_
// #define SerialD Serial
// #define _DEGUB_MESSAGE(a)               \
//     SerialD.print(millis()); \
//     SerialD.print(": ");     \
//     SerialD.println(a)
// #define _DEGUB_PRINT(a) SerialD.print(a)
// #define _DEGUB_PRINTLINE(a) SerialD.println(a)
// #define _DEGUB_PRINTHEX(a) SerialD.println(a, HEX)
// #else
// #define _DEGUB_MESSAGE(a)
// #define _DEGUB_PRINT(a)
// #define _DEGUB_PRINTLINE(a)
// #define _DEGUB_PRINTHEX(a)
// #endif
// // end of debugging macros

#include <esp_config.h>
#include <frame_data.h>
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>

// MatrixPanel_I2S_DMA dma_display;
MatrixPanel_I2S_DMA *dma_display = nullptr;
VirtualMatrixPanel *virtualDisp = nullptr;

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

#include <FastLED.h>

uint16_t time_counter = 0, cycles = 0, fps = 0;
unsigned long fps_timer;

CRGB currentColor;
CRGBPalette16 palettes[] = {HeatColors_p, LavaColors_p, RainbowColors_p, RainbowStripeColors_p, CloudColors_p};
CRGBPalette16 currentPalette = palettes[0];

CRGB ColorFromCurrentPalette(uint8_t index = 0, uint8_t brightness = 255, TBlendType blendType = LINEARBLEND)
{
    return ColorFromPalette(currentPalette, index, brightness, blendType);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting...");

    HUB75_I2S_CFG mxconfig(
        PANEL_RES_X,
        PANEL_RES_Y,
        PANEL_CHAIN);
    mxconfig.i2sspeed = mxconfig.HZ_20M;
    mxconfig.driver = mxconfig.SHIFTREG;
    mxconfig.clkphase = false;
    mxconfig.latch_blanking = 1;
    // mxconfig.double_buff = true;

    dma_display = new MatrixPanel_I2S_DMA(mxconfig);

    dma_display->setBrightness8(192); // range is 0-255, 0 - 0%, 255 - 100%

    // Allocate memory and start DMA display
    if (not dma_display->begin())
        Serial.println("****** !KABOOM! I2S memory allocation failed ***********");

    virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, VIRTUAL_MATRIX_CHAIN_TYPE);
    virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));

    currentPalette = RainbowColors_p;
    fps_timer = millis();
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

// void loop()
// {
//     // draw rect
//     virtualDisp->fillRect(x, y, rectWidth, rectHeight, virtualDisp->color565(color.r, color.g, color.b));

//     // move rect diagonally
//     x += directionX;
//     y += directionY;

//     // change direction if we hit the edge
//     if (x == SCREEN_WIDTH - rectWidth || x == 0)
//     {
//         directionX *= -1;
//         color = hue2rgb(random(0, 255));
//     }
//     if (y == SCREEN_HEIGHT - rectHeight || y == 0)
//     {
//         directionY *= -1;
//         color = hue2rgb(random(0, 255));
//     }

//     // delay
//     delay(10);
//     virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));
// }

uint8_t r, g, b;
uint8_t frame = 0;
void loop()
{
    Serial.print("frame ");
    Serial.println(frame);
    dma_display->setBrightness8(3); // range is 0-255, 0 - 0%, 255 - 100%
    for (int y = 0; y <= 63; y++)
    {
        for (int x = 0; x <= 63; x++)
        {
            r = color_array[pixel_array[frame * 64 * 64 + y * 64 + x]];
            virtualDisp->drawPixel(x, y, virtualDisp->color565(r, g, b));
        }
    }
    frame = (frame + 1) % frame_count;
    delay(33);
    virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));
}

// void loop()
// {
//     dma_display->setBrightness8(20); // range is 0-255, 0 - 0%, 255 - 100%
//     for (int x = 0; x < 64; x++)
//     {
//         for (int y = 0; y < 64; y++)
//         {
//             int16_t v = 0;
//             uint8_t wibble = sin8(time_counter);
//             v += sin16(x * wibble * 3 + time_counter);
//             v += cos16(y * (128 - wibble) + time_counter);
//             v += sin16(y * x * cos8(-time_counter) / 8);

//             currentColor = ColorFromPalette(currentPalette, (v >> 8) + 127); //, brightness, currentBlendType);
//             virtualDisp->drawPixelRGB888(x, y, currentColor.r, currentColor.g, currentColor.b);
//         }
//     }

//     ++time_counter;
//     ++cycles;
//     ++fps;

//     if (cycles >= 1024)
//     {
//         time_counter = 0;
//         cycles = 0;
//         currentPalette = palettes[random(0, sizeof(palettes) / sizeof(palettes[0]))];
//     }

//     // print FPS rate every 5 seconds
//     // Note: this is NOT a matrix refresh rate, it's the number of data frames being drawn to the DMA buffer per second
//     if (fps_timer + 5000 < millis())
//     {
//         Serial.printf_P(PSTR("Effect fps: %d\n"), fps / 5);
//         fps_timer = millis();
//         fps = 0;
//     }
// } // end loop