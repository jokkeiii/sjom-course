// Variables for adc value, input and output voltages
int adc_value, input;
float output;

// Variable for tau, 100 ms
int t = 100;

void setup() {
  // Set digital pin 5 as an output
  pinMode(5, OUTPUT);
  // Set analog pin A0 as an input
  pinMode(A0, INPUT);
  // Initialize serial communication with a baud rate of 9600
  Serial.begin(9600);
}

void loop() {

  // Set input to 5v
  input = 5;

  // Turn on the digital pin 5
  digitalWrite(5, HIGH);

  // Read the analog value from pin A0 and store it in the variable adc_value
  adc_value = analogRead(A0);
  // Convert the ADC value to voltage and store it in the output
  output = (adc_value * 5.0) / 1023.0;

  Serial.print("Output:");
  Serial.println(output);

  // Print output after tau, 2tau and 3tau
  for (int i = 1; i < 4; i++) {
    delay(t);
    Serial.print("T:");
    Serial.println(i);

    // Read the analog value from pin A0 and store it in the variable adc_value
    adc_value = analogRead(A0);
    // Convert the ADC value to voltage and store it in the output
    output = (adc_value * 5.0) / 1023.0;

    Serial.print("Output:");
    Serial.println(output);
  }

  delay(200);

  // Print information to the serial monitor
  Serial.print("Input:");
  Serial.print(input);
  Serial.print(",");
  Serial.print("Output:");
  Serial.println(output);

  // Turn off the digital pin 5
  digitalWrite(5, LOW);
  // Pause for 500 milliseconds
  delay(500);

  // Read the analog value from pin A0 again
  adc_value = analogRead(A0);
  // Convert the ADC value to voltage using the formula and store it in the
  // output variable
  output = (adc_value * 5.0) / 1023.0;

  // Set input to 0v
  input = 0;

  // Print information to the serial monitor
  Serial.print("Input:");
  Serial.print(input);
  Serial.print(",");
  Serial.print("Output:");
  Serial.println(output);
}
