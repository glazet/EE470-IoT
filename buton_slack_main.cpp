include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = ""; // must be exactly as it apears - case sensitive
const char* password = "";
String url     = "https://maker.ifttt.com/trigger/button_slack/json/with/key/HHYR9SSlKa-JO9Yr5aPmk";
const int button = D0;
int trigger = 0;

void setup() {
  Serial.begin(9600); //typically 9600
  pinMode(button, INPUT);
  
   // (A) Start connecting to the WiFI
  Serial.println("Connecting to WiFi"); 
  WiFi.begin(ssid, password); // Connection to WiFi Starts until status()=WL_CONNECTED
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("."); // waiting to get connected
  }
  Serial.println("Connected to WiFi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
	
	  char command;
	  trigger = digitalRead(button);

    if (trigger == LOW){
      if (https.begin(client, url)) { // start the connection 1=started / 0=failed

      int httpCode = https.GET(); // choose GET or POST method
      //int httpCode = https.POST(url); // need to include URL
      
      Serial.println("Response code <--: " + String(httpCode)); // print response code: e.g.,:200
      if (httpCode > 0) {
        Serial.println(https.getString()); // this is the content of the get request received
      }
      https.end(); // end of request
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }
    }
  }
  delay(1000); // delay between each REQUEST to the server
}
