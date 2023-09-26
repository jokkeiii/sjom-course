volatile int counter = 0;

void plus_one()
{
    counter++;
    Serial.println(counter);
}

int buttonState = 0;

void setup()
{
    Serial.begin(9600);
    delay(2000);
    pinMode(2, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(2), plus_one, RISING);
    Serial.println("HERE!");
}

void loop()
{
    // read the state of the pushbutton value
    buttonState = digitalRead(2);

    // check if pushbutton is pressed.  if it is, the
    // buttonState is LOW
    if (buttonState == LOW)
    {
        // turn LED on
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        // turn LED off
        digitalWrite(LED_BUILTIN, LOW);
    }
    delay(10); // Delay a little bit to improve simulation performance
}