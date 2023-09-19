void setup()
{
    // give me time to attach serial monitor
    delay(3000);
    Serial.begin(9600);
    int number_1 = 170;
    int number_2 = 204;

    // number_1 AND number_2
    Serial.println(number_1 & number_2, BIN);

    // number_1 OR number_2
    Serial.println(number_1 | number_2, BIN);

    // number_1 XOR number_2
    Serial.println(number_1 ^ number_2, BIN);

    // NOT number_1
    Serial.println(~number_1, BIN);

    // NOT number_2
    Serial.println(~number_2, BIN);
}

void loop()
{
}