// #define ESP32_WROOM_32
#define ESP32_S3

#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module.
#define PANEL_RES_Y 32 // Number of pixels tall of each INDIVIDUAL panel module.

#define NUM_ROWS 2                     // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 1                     // Number of INDIVIDUAL PANELS per ROW
#define PANEL_CHAIN NUM_ROWS *NUM_COLS // total number of panels chained one to another
#define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP

#ifdef ESP32_WROOM_32
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
#endif

#ifdef ESP32_S3
#define R1_PIN_DEFAULT 4
#define G1_PIN_DEFAULT 5
#define B1_PIN_DEFAULT 6
#define R2_PIN_DEFAULT 7
#define G2_PIN_DEFAULT 15
#define B2_PIN_DEFAULT 46

#define A_PIN_DEFAULT 8
#define B_PIN_DEFAULT 16
#define C_PIN_DEFAULT 3
#define D_PIN_DEFAULT 17
#define E_PIN_DEFAULT -1

#define LAT_PIN_DEFAULT 18
#define OE_PIN_DEFAULT 9
#define CLK_PIN_DEFAULT 10
#endif