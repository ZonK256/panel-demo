#include <Arduino.h>
int pins[] = {4, 5, 6, 7, 15, 16, 17, 18, 8, 3, 46, 9, 10};

void setup()
{
    for (int i = 0; i < 13; i++)
    {
        pinMode(pins[i], OUTPUT);
    }
}

void loop()
{
    delay(50);
    for (int i = 0; i < 13; i++)
    {
        digitalWrite(pins[i], HIGH);
    }
    delay(50);
    for (int i = 0; i < 13; i++)
    {
        digitalWrite(pins[i], LOW);
    }
}