/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float v = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.println(voltage);
  float Rt = 10 * v / (5 - v);
  // Calculate temp (Kelvin)
  float tempK = 1 / (log(Rt / 10) / 3950 + 1 /  (273.15 + 6));
  // Calculate temp (Celsius)
  float tempC  = tempK - 273.15;

  // Send result to comp node through serial port
  Serial.print("Current temp is: ");
  Serial.print(tempK);
  Serial.print(" K, ");
  Serial.print(tempC);
  Serial.println(" C");
  delay(5500);

  // need to put time in the output also
}
