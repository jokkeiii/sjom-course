uint8_t sensor_pin_1 = A4; // Määritetään sensorin pinni (analoginen pinni A4)
uint8_t sensor_pin_2 = A7; // Määritetään sensorin pinni (analoginen pinni A7)
int val;                   // Väliaikainen muuttuja ADC-lukemille

void setup()
{
    Serial.begin(9600); // Käynnistetään serial monitor
}

void loop()
{

    uint16_t sensor_value_1 = ADC_read(4); // Luetaan sensorin arvo muuttujaan 1
    float voltage_1 = sensor_value_1 / 1023.0 * 5.0;  // Lasketaan jännite 1

    Serial.print("Voltage 1 is: ");
    Serial.println(voltage_1);
    Serial.println();

    delay(200);

    uint16_t sensor_value_2 = ADC_read(7); // Luetaan sensorin arvo muuttujaan 2
    float voltage_2 = sensor_value_2 / 1023.0 * 5.0;  // Lasketaan jännite 2

    Serial.print("Voltage 2 is: ");
    Serial.println(voltage_2);
    Serial.println();

    delay(2000);
}

void ADC_init(uint8_t ch) {
    ADMUX = 0x00;
    ADCSRA = 0x00;
    // Asetetaan ADCSRB rekisteri nolliksi
    //ADCSRB = 0x00;   

    // Asetetaan referenssijännite ja ADC-muunnoskanava
    //ADMUX |= (1 << REFS0);

    if (ch == 4) {
      ADMUX |= (1 << REFS0) | (1 << MUX2);
      Serial.println("pin4");

    } else if (ch == 7 ){
      ADMUX |= (1 << REFS0) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
      Serial.println("pin7");
    }

    else Serial.println("Cannot identify pin");
    ADCSRA |= (1 << ADEN); // Aktivoidaan ADC
    //ADCSRB = 0x00;         


}

uint16_t ADC_read(uint8_t ch)
{
    ADC_init(ch);

    // aloitetaan muunnos
    ADCSRA |= (1 << ADSC); // Käynnistetään ADC-muunnos

    if (ch == 4)
    {
        while (ADCSRA & B00001000) // Odotetaan, että muunnos 1 on valmis
        {
            ;
        }
    }
    else
    {
        while (ADCSRA & B01000000) // Odotetaan, että muunnos 1 on valmis
        {
            ;
        }
    }

    return ADC; // Palautetaan ADC arvo
}
