#include <ESP8266WiFi.h>
String apiKey = "S83GPH1VKLDWANRE";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "DANGER SPOT";     // replace with your wifi ssid and wpa2 key
const char *pass =  "password@34";
const char* server = "api.thingspeak.com";
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
 float k= (sensorvalue*(51.0/1023.0)*50);
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(sensorvalue);
                             postStr +="&field2=";
                             postStr += String(k);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("voltage: ");
                             Serial.print(sensorvalue);
                             Serial.print(" wind speed ");
                             Serial.print(k);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}

