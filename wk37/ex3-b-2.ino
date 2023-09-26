void setup()
{
    Serial.begin(9600);
    // give me time to attach serial monitor
    delay(2000);
    // set b register ports D8-D13 as outputs, and last 2 bits as inputs
    DDRB = B00000000;
    // set last 2 bits to internal pullup
    PORTB = B11000000;

    // print setup data
    Serial.println("SETUP:");
    Serial.println(PORTB, BIN);

    // set the fourth bit to 1, internal pullup
    PORTB |= 1 << PB3;

    // print data
    Serial.println(PORTB, BIN);
}

void loop()
{
}