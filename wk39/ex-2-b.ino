volatile bool toggle_blink = false;
unsigned long previousMillis = 0;
unsigned long interval = 100;
int state = 0;

void callback()
{
    toggle_blink = !toggle_blink;
}

void setup()
{
    // set all d register ports as outputs except pin 3
    DDRD = B11110111;
    // set pin 3 as internal pullup
    PORTD = B00001000;

    attachInterrupt(digitalPinToInterrupt(3), callback, FALLING);

    // startup sequence
    // turn the green LED on (HIGH is the voltage level)
    PORTD |= B10000000;
    delay(1000); // Wait for 1000 millisecond(s)
    // turn the green LED off and yellow on
    PORTD &= B01111111;
    PORTD |= B01000000;
    delay(1000);
    // yellow LED off and red on
    PORTD &= B10111111;
    PORTD |= B00100000;
    delay(1000);
    // red LED off
    PORTD &= B11011111;
    delay(1000);
}

void loop()
{
    // if toggle_blink is true
    if (toggle_blink)
    {
        // start yellow led blinking

        // yellow LED on
        PORTD |= B01000000;
        delay(250);
        // yellow LED off
        PORTD &= B10111111;
        delay(250);
    }
    // if false continue traffic lights
    else
    {
        // green LED on
        PORTD |= B10000000;
        delay(3000);
        // green LED off and yellow on
        PORTD &= B01111111;
        PORTD |= B01000000;
        delay(1000);
        // yellow LED off and red on
        PORTD &= B10111111;
        PORTD |= B00100000;
        delay(2000);
        // yellow LED on
        PORTD |= B01000000;
        delay(1000);
        // yellow and red LEDs off
        PORTD &= B10011111;
    }
}