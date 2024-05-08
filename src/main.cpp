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
#define TEST_PINS false

#include "esp_config.h"
#include "frame_data.h"
#include "examples/examples.h"

#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <FastLED.h>

#if TEST_PINS
#include "../tests/pin_test.cpp"
#else
ExampleType example = RAINBOW;
const uint8_t BRIGHTNESS = 100;

MatrixPanel_I2S_DMA *dma_display = nullptr;
VirtualMatrixPanel *virtualDisp = nullptr;
#endif

void setup()
{
#if TEST_PINS
    testSetup();
#else
    HUB75_I2S_CFG::i2s_pins _pins = {R1, G1, BL1, R2, G2, BL2, CH_A, CH_B, CH_C, CH_D, CH_E, LAT, OE, CLK};
    HUB75_I2S_CFG mxconfig(
        PANEL_RES_X,
        PANEL_RES_Y,
        PANEL_CHAIN,
        _pins);
    mxconfig.i2sspeed = mxconfig.HZ_20M;
    mxconfig.driver = mxconfig.SHIFTREG;
    mxconfig.clkphase = false;
    mxconfig.latch_blanking = 1;

    dma_display = new MatrixPanel_I2S_DMA(mxconfig);
    dma_display->setBrightness8(BRIGHTNESS);

    if (not dma_display->begin())
        Serial.println("****** !KABOOM! I2S memory allocation failed ***********");

    virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, VIRTUAL_MATRIX_CHAIN_TYPE);
    virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));

    switch (example)
    {
    case ExampleType::HELLO_WORLD:
        setupHelloWorld(dma_display);
        break;
    case ExampleType::RAINBOW:
        setupRainbow(virtualDisp, dma_display);
        break;
    case ExampleType::IMAGE_SEQUENCE:
        setupImageSequence(virtualDisp);
        break;
    case ExampleType::BOUNCING_LOGO:
        setupBouncingLogo(virtualDisp);
        break;
    case ExampleType::COLOR_TEST:
        setupColorTest(virtualDisp);
        break;
    case ExampleType::ZDITM:
        setupZDITM(virtualDisp);
        break;
    }
#endif
}
void loop()
{
#if TEST_PINS
    testLoop();
#else
    switch (example)
    {
    case ExampleType::HELLO_WORLD:
        loopHelloWorld(dma_display);
        break;
    case ExampleType::RAINBOW:
        loopRainbow(virtualDisp, dma_display);
        break;
    case ExampleType::IMAGE_SEQUENCE:
        loopImageSequence(virtualDisp);
        break;
    case ExampleType::BOUNCING_LOGO:
        loopBouncingLogo(virtualDisp);
        break;
    case ExampleType::COLOR_TEST:
        loopColorTest(virtualDisp);
        break;
    case ExampleType::ZDITM:
        loopZDITM(virtualDisp);
        break;
    }
#endif
}