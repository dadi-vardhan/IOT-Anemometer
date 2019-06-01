#include <ESP8266WiFi.h>
#include <Wire.h>
//String apiKey = "o.FRbEvnGXo0jj59ufDjLrl0xGHcMmLj2X";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "vishnu";     // replace with your wifi ssid and wpa2 key
const char *pass =  "dadi1234";

int ledPin = 9;
WiFiClient client;
void setup() {
 Serial.begin(9600);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 WiFi.begin(ssid, pass);
 while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
      }

void loop() {
 float sensorvalue = analogRead(A0);
 float k= (sensorvalue*(51.0/1023.0)*50);}
 char *api_server = "api.pushingbox.com";
char *deviceId = "v10BAFBDA2376E5E";
  void sendNotification(float sensorvalue, float k) 
   { Serial.println("Sending notification to " + String(api_server));
    if (client.connect(api_server, 80)) {
        Serial.println("Connected to the server");
        String message = "devid=" + String(deviceId) +
            "&voltage=" + String(sensorvalue) +
            "&windspeed=" + String(k) +
            "\r\n\r\n";
        client.print("POST /pushingbox HTTP/1.1\n");
        client.print("Host: api.pushingbox.com\n");
        client.print("Connection: close\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(message.length());
        client.print("\n\n");
        client.print(message);
    }
    client.stop();
    Serial.println("Notification sent!");
}

