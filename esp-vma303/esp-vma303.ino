
// following are vma303 variable and pinouts
int GLED = 13; // Wet Indicator at Digital PIN D13
int RLED = 12; // Dry Indicator at Digital PIN D12
int SENSE = 12; // Soil Sensor input at Analog input PIN12 on esp32 devkitv1
int value = 0;
int LED_BUILTIN = 2;

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("VMA303 Soil Moisture Sensor initiated!");
  Serial.println("All systems go for launch");
}

void loop() {
  // put your main code here, to run repeatedly:

}
