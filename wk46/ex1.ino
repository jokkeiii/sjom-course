// Example program using Arduino IDE Serial Plotter

void setup() {
  // We use fast communication in this example
  Serial.begin(115200); 
  delay(10); 
}

void loop() {
  int variable1 = analogRead(A0);
  //int variable2 = analogRead(A1);
  int last_variable = millis()%100; // Ramps from 0 to 100

  Serial.print("Pin_A0:");  // First variable label
  Serial.print(variable1);  // First variable data
  Serial.print(",");        // Separator
  //Serial.print("Pin_A1:");  // 2nd variable label
  //Serial.print(variable2);  // 2nd variable data
  //Serial.print(",");        // Separator
  Serial.print("Ramp:");    // Last variable label
  Serial.println(last_variable);  // Last variable data

  // Small delay for fast updates
  delay(2);
}