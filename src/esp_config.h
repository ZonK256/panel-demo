#pragma once

#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module.
#define PANEL_RES_Y 32 // Number of pixels tall of each INDIVIDUAL panel module.

#define NUM_ROWS 2                     // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 1                     // Number of INDIVIDUAL PANELS per ROW
#define PANEL_CHAIN NUM_ROWS *NUM_COLS // total number of panels chained one to another
#define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP

#ifdef ESP32_WROOM_32 // Defined in platformio.ini if using ESP32-WROOM-32
#define R1 25
#define G1 26
#define BL1 27
#define R2 14
#define G2 12
#define BL2 13

#define CH_A 23
#define CH_B 19
#define CH_C 5
#define CH_D 17
#define CH_E -1

#define CLK 16
#define LAT 4
#define OE 15
#endif

#ifdef ESP32_S3 // Defined in platformio.ini if using ESP32-S3
#define R1 4
#define G1 5
#define BL1 6
#define R2 7
#define G2 15
#define BL2 46

#define CH_A 8
#define CH_B 16
#define CH_C 3
#define CH_D 17
#define CH_E -1

#define CLK 12
#define LAT 18
#define OE 9
#endif