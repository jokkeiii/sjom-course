#include <avr/wdt.h>

const int led_pin = 9;

void setup()
{
    Serial.begin(9600);
    Serial.println("Ollaan setupissa");

    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, HIGH);
    wdt_enable(WDTO_4S);
}

void loop()
{
    for (int i{}; i < 5; ++i)
    {
        delay(1000);
        digitalWrite(led_pin, not digitalRead(led_pin));
        wdt_reset();
    }
}
