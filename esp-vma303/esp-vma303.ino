
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
  // vma303 loop 
  value= analogRead(SENSE);  // analog input gpio12
  value= value/10;
  Serial.print("Flowerpot soil moisture: ");
  Serial.print(value);
  Serial.print("\n");
  
  if(value<50) {
      digitalWrite(GLED, HIGH);
  } else {
      digitalWrite(RLED,HIGH);
   }
   delay(55777);
   
   digitalWrite(GLED,LOW);
   digitalWrite(RLED, LOW);

}
