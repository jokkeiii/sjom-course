void setup()
{
    Serial.begin(9600);
    // give me time to attach serial monitor
    delay(2000);
    // set b register ports as outputs
    DDRB = B11111111;
    // set all bits to low
    PORTB = B00000000;

    // print setup data
    Serial.println("SETUP:");
    Serial.println(PORTB, BIN);

    // set pins 5, 3, 2 and 0 to high
    PORTB |= B00101101;

    // print data
    Serial.println(PORTB, BIN);

    delay(1500);

    // set pins 1 and 4 to high
    PORTB |= B00010010;

    // print the data
    Serial.println(PORTB, BIN);

    delay(1500);

    // set all bits to 0
    PORTB = B00000000;

    // print the data
    Serial.println(PORTB, BIN);
}

void loop()
{
}