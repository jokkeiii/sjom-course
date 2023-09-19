void setup()
{
    // set all d register ports as outputs
    DDRD = B11111111;

    // startup sequence

    // turn the green LED on (HIGH is the voltage level)
    PORTD = B10000000;
    delay(1000); // Wait for 1000 millisecond(s)
    // turn the green LED off and yellow on
    PORTD = B01000000;
    delay(1000);
    // red LED on and yellow off
    PORTD = B00100000;
    delay(1000);
    // red LED off
    PORTD = B00000000;
    delay(1000);
}

void loop()
{
    // green LED on
    PORTD = B10000000;
    delay(3000);
    // green LED off and yellow on
    PORTD = B01000000;
    delay(1000);
    // yellow LED off and red on
    PORTD = B00100000;
    delay(2000);
    // yellow LED on
    PORTD = B01100000;
    delay(1000);
    // yellow and red LEDs off
    PORTD = B00000000;
}