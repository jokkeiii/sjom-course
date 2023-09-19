int green_led = 13;
int yellow_led = 11;
int red_led = 9;

void setup()
{
    pinMode(green_led, OUTPUT);
    pinMode(yellow_led, OUTPUT);
    pinMode(red_led, OUTPUT);
    // startup sequence
    //
    // turn the green LED on (HIGH is the voltage level)
    digitalWrite(green_led, HIGH);
    delay(1000); // Wait for 1000 millisecond(s)
    // turn the green LED off by making the voltage LOW
    digitalWrite(green_led, LOW);
    // yellow LED on and off
    digitalWrite(yellow_led, HIGH);
    delay(1000);
    digitalWrite(yellow_led, LOW);
    // red LED on and off
    digitalWrite(red_led, HIGH);
    delay(1000);
    digitalWrite(red_led, LOW);
    delay(1000);
}

void loop()
{
    digitalWrite(green_led, HIGH);
    delay(3000);
    digitalWrite(green_led, LOW);
    // turn the LED on (HIGH is the voltage level)
    digitalWrite(yellow_led, HIGH);
    delay(1000); // Wait for 1000 millisecond(s)
    digitalWrite(yellow_led, LOW);
    // turn the LED on (HIGH is the voltage level)
    digitalWrite(red_led, HIGH);
    delay(2000); // Wait for 1000 millisecond(s)
    // turn the LED off by making the voltage LOW
    digitalWrite(yellow_led, HIGH);
    delay(1000);
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, LOW);
}