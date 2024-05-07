#ifndef PIN_TEST_CPP
#define PIN_TEST_CPP

#include <Arduino.h>
#include "esp_config.h"

int pins[] = {CLK, R1, G1, BL1, R2, G2, BL2, CH_A, CH_B, CH_C, CH_D, CH_E, LAT, OE};
int num_pins = sizeof(pins) / sizeof(pins[0]);

void testSetup()
{
    for (int i = 0; i < num_pins; i++)
    {
        pinMode(pins[i], OUTPUT);
    }
}

void testLoop()
{
    delay(50);
    for (int i = 0; i < num_pins; i++)
    {
        digitalWrite(pins[i], HIGH);
    }
    delay(50);
    for (int i = 0; i < num_pins; i++)
    {
        digitalWrite(pins[i], LOW);
    }
}
#endif // PIN_TEST_CPP