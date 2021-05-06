// flowerpot project -- [arduino uno micro controller, dht11 temp/humidity sensor,
// vma303 soil moisture sensor, esp32 dev kit radio component
// IoT with Arduino experimental course -- Haaga-Helia UAS
//28-4-2021 Helsinki, Finland

// dht 11 libraries and variables
#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"

#define DHTTYPE DHT11
//here we use 14 of ESP32 to read data
#define DHTPIN A14  // the number of the DHT11 sensor pin14 on esp32 dev kit v1

 
DHT dht(DHTPIN, DHTTYPE); // this is DHT object of type at pin

// following are vma303 variable and pinouts
int GLED = 13; // Wet Indicator at Digital PIN D13
int RLED = 12; // Dry Indicator at Digital PIN D12
int SENSE = 12; // Soil Sensor input at Analog input PIN12 on esp32 devkitv1
int value = 0;
int LED_BUILTIN = 2;

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  dht.begin();
  Serial.println(F("DHT11 initiated!"));
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  Serial.println("VMA303 Soil Moisture Sensor initiated!");
  Serial.println("All systems go for launch");
}

void loop() {
   // blink 187 esp subroutine follows 
   // this loop does a double blink
   //digitalWrite(LED_BUILTIN, HIGH);
   //delay(337);
   //digitalWrite(LED_BUILTIN, LOW);
   //delay(3337); // waiting period
   //digitalWrite(LED_BUILTIN, HIGH);
   //delay(337);
   //digitalWrite(LED_BUILTIN, LOW);
   //delay(337);
   
   // Reading temperature or humidity takes about 250 milliseconds!
   // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
   float h = dht.readHumidity();
   // Read temperature as Celsius (the default)
   float t = dht.readTemperature();
   // Read temperature as Fahrenheit (isFahrenheit = true)
   float f = dht.readTemperature(true);

   // Check if any reads failed and exit early (to try again).
   if (isnan(h) || isnan(t) || isnan(f)) {
     Serial.println(F("Failed to read from DHT sensor!"));
     return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  value= analogRead(SENSE);
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
