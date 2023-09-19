void setup()
{
    Serial.begin(9600);
    // give me time to attach serial monitor
    delay(2000);
    // set b register ports D8-D13 as outputs, and last 2 bits as inputs
    DDRB = B00111111;
    // set last 2 bits to internal pullup
    PORTB = B11000000;

    // print setup data
    Serial.println("SETUP:");
    Serial.println(PORTB, BIN);

    // set all bits to 1
    PORTB = B11111111;

    // print data
    Serial.println(PORTB, BIN);

    // first command
    PORTB = 1 << 4;

    // print the data
    Serial.println(PORTB, BIN);

    // set all bits to 1
    PORTB = B11111111;

    // print the data
    Serial.println(PORTB, BIN);

    // second command
    PORTB |= 1 << 4;

    // print the data
    Serial.println(PORTB, BIN);
}

void loop()
{
}