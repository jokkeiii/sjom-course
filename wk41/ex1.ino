const int ledPin = 13;
byte ledState = HIGH;
int count = 0;

void setup()
{
    pinMode(ledPin, OUTPUT);

    // Aseta Timer/Counter1 laskuriarvoksi 0
    TCNT1 = 0x0000;
    // Aseta normaali toimintatila
    TCCR1A = 0x00;
    // Aseta kellotaajuus prescaler-arvoksi 1024
    TCCR1B = (1 << CS12) | (0 << CS11) | (1 << CS10);
    // Tyhjennetään TIFR1 OCF1A ja OCF1B
    TIFR1 = (1 << OCF1A) | (1 << OCF1B);
    // Tyhjennä ylivuotolippu
    TIFR1 = (1 << TOV1);
}

void loop()
{
    // Tarkista onko Timer/Counter1:n ylivuotolippu asetettu
    if ((TIFR1 & B1) == true)
    {
        count++;
        // Tyhjennä ylivuotolippu
        TIFR1 = (1 << TOV1);
    }
    if (count == 50)
    {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
        count = 0;
    }
}
