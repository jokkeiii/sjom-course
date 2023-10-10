enum : int32_t
{
    input_pin = A0,
    output_pin = 2,
    nominal_resistance = 47000,
    nominal_temperature = 25,
    sample_amount = 10,
    beta = 3950,
};

void setup(void)
{
    pinMode(output_pin, OUTPUT);
    Serial.begin(9600);
}

void loop(void)
{
    int32_t samples{};

    // Take voltage readings from the voltage divider
    digitalWrite(output_pin, HIGH);
    for (uint8_t i{}; i < sample_amount; ++i)
    {
        samples += analogRead(input_pin);
        delay(10);
    }
    digitalWrite(output_pin, LOW);

    // Calculate the average value
    float average{samples / sample_amount};
    Serial.println("\n\n");
    Serial.print("ADC readings: ");
    Serial.println(average);

    // Convert the analog reading to resistance
    float resistance{(1023.0 / samples - 1.0) * nominal_resistance};
    Serial.print("Thermistor resistance: ");
    Serial.println(resistance);

    // Use the Steinhart-Hart equation to calculate temperature in Celsius
    float temperature = resistance / nominal_resistance; // (R/Ro)
    temperature = log(temperature);                      // ln(R/Ro)
    temperature /= beta;                                 // 1/B * ln(R/Ro)
    temperature += 1.0 / (nominal_temperature + 273.15); // + (1/To)
    temperature = 1.0 / temperature;                     // Invert
    temperature -= 273.15;                               // Convert to Celsius

    // Print the result to the serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");

    delay(1000);
}
