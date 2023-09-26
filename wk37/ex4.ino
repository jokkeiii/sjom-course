void setup()
{
    Serial.begin(9600);
    // give me time to attach serial monitor
    delay(2000);
    // set b register ports as inputs other than 5
    DDRB = B00100000;
    // set bit 5 to 1
    PORTB = B00100000;
}

void loop()
{

    // print data
    Serial.println("FIRST: ");
    Serial.println(PORTB, BIN);

    // set bit 5 to 1
    // using PINx register, the data will be toggled rather than setting it to whatever is written
    PINB = B00100000;

    // print data
    Serial.println("SECOND: ");
    Serial.println(PORTB, BIN);

    delay(1500);
}