// flowerpot project -- [arduino uno micro controller, dht11 temp/humidity sensor,
// vma303 soil moisture sensor, esp32 dev kit radio component
// IoT with Arduino experimental course -- Haaga-Helia UAS
//28-4-2021 Helsinki, Finland -- kodaja ###

// dht 11 libraries and variables
#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"

#define DHTTYPE DHT11

int DHTPin = 10;  // the number of the DHT11 sensor pin
DHT dht(DHTPin, DHTTYPE); // this is DHT object of type at pin

// following are vma303 variable and pinouts
int GLED = 13; // Wet Indicator at Digital PIN D13
int RLED = 12; // Dry Indicator at Digital PIN D12
int SENSE = 0; // Soil Sensor input at Analog PIN A0
int value = 0;

void setup() {
  Serial.begin(9600);

  dht.begin();
  Serial.println(F("DHT11 initiated!"));
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  Serial.println("VMA303 Soil Moisture Sensor initiated!");
  Serial.println("All systems go for launch");
}

void loop() {
  // blink 187 esp subroutine follows 
  // this loop does a triple
  digitalWrite(LED_BUILTIN, HIGH);
  delay(337);
  digitalWrite(LED_BUILTIN, LOW);
  delay(3337); // waiting period
  digitalWrite(LED_BUILTIN, HIGH);
  delay(337);
  digitalWrite(LED_BUILTIN, LOW);
  delay(337);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(337);
  digitalWrite(LED_BUILTIN, LOW);
  delay(337);
  
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
