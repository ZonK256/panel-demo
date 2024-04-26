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

#define R1_PIN_DEFAULT 25
#define G1_PIN_DEFAULT 26
#define B1_PIN_DEFAULT 27
#define R2_PIN_DEFAULT 14
#define G2_PIN_DEFAULT 12
#define B2_PIN_DEFAULT 13

#define A_PIN_DEFAULT 23
#define B_PIN_DEFAULT 19
#define C_PIN_DEFAULT 5
#define D_PIN_DEFAULT 17
#define E_PIN_DEFAULT -1

#define LAT_PIN_DEFAULT 4
#define OE_PIN_DEFAULT 15
#define CLK_PIN_DEFAULT 16

#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>

// MatrixPanel_I2S_DMA dma_display;
MatrixPanel_I2S_DMA *dma_display = nullptr;
VirtualMatrixPanel *virtualDisp = nullptr;

#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module.
#define PANEL_RES_Y 32 // Number of pixels tall of each INDIVIDUAL panel module.

#define NUM_ROWS 2                     // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 1                     // Number of INDIVIDUAL PANELS per ROW
#define PANEL_CHAIN NUM_ROWS *NUM_COLS // total number of panels chained one to another
#define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP

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

void loop()
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

    // delay
    delay(10);
    virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));
}