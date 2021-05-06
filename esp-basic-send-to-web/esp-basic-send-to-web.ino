#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include "HTTPClient.h" //http client

// network settings
const char* ssid       = "your_ssid";
const char* password   = "your_password";
unsigned long lastTime = 0;
unsigned long timerDelay = 10000; //this is ten seconds.
//String data;

//your_dir_name is your first name in lower case letters
//do not change anything else in the serverName

const char* serverName = "http://www.sabulo.com/iot/your_first_name/iotwrite.php";

// variables
String myString = "This is what you want to say";


void setup() {
  Serial.begin(9600); //start serial to device
  //connect to WiFi
  Serial.print("Connecting to network" );
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
}

void loop() {

  //sending data to the server:
  if ((millis() - lastTime) > timerDelay) {
    Serial.println("add data to web");
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // If you need an HTTP request with a content type: text/plain
      http.addHeader("Content-Type", "text/plain");
      String httpRequestData = "My String: " + myString;
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      Serial.println("HTTP Response code: ");
      Serial.println(httpRequestData);

      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

/* The PHP on the server looks like this:
 *  
 *  <?php
    $_POST = file_get_contents('php://input');
    $myYear = date("d.m.Y");
    $myHour = date("H:i");
    $myFile = "humitime.txt";
    $fh = fopen($myFile, 'a') or die("can't open file");
    fwrite($fh, $myYear . " " .  $myHour);
    fwrite($fh, "\t");
    fwrite($fh, $_POST);
    fwrite($fh, "\n");    
    fclose($fh);
    ?> 
*/
