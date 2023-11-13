#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>  // must be installed

const char* ssid = "";
const char* password = "";
String url = "https://trentglaze.000webhostapp.com/button_led/results.txt";  // Change this to your server address

const int LED_PIN = D2;  // Change this to the pin where your LED is connected
const int BUTTON_PIN = D0;  // Change this to the pin where your switch is connected
int switchState = 0;

DynamicJsonDocument doc(1024);

void setup () {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  delay(10); // just a short delay
  Serial.println("");
  
  // (A) Start connecting to teh WiFI
  Serial.println("Connecting to WiFi"); 
  WiFi.begin(ssid, password); // Connection to WiFi Starts until status()=WL_CONNECTED
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("."); // waiting to get connected
  }
  Serial.println("Connected to WiFi");
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;

    String fullUrl = url; // preparing the full URL
    Serial.println("Requesting: --> " + fullUrl);
    if (https.begin(client, fullUrl)) { // start the connection 1=started / 0=failed

      int httpCode = https.GET(); // choose GET or POST method
      //int httpCode = https.POST(fullUrl); // need to include URL
      if (httpCode > 0) {
        Serial.println(https.getString()); // this is the content of the get request received
        deserializeJson(doc,https.getString()); // deserialize the JSON file
        //deserializeJson(doc,https.getString()); // deserialize the JSON format into keys and values
        String ledState = doc[0-3]; // get the value 
        //Serial.println(ledState); 

        if (https.getString() == "on"){
            digitalWrite(LED_PIN, HIGH);
        }
        else if (https.getString() == "off")
        {
          digitalWrite(LED_PIN, LOW);
        }
        
      }
      https.end(); // end of request
    } else {
        Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
  delay(30000); // delay between each REQUEST to the server

}
