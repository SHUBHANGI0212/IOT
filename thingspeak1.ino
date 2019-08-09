#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
WiFiClient client;
String thingSpeakAddress = "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;
HTTPClient http;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("electromodule", "electromodule@456");
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(3000);
    Serial.print("...");
  }
  Serial.println("CONNECTED");
}

void loop() {
  // put your main code here, to run repeatedly:
  request_string = thingSpeakAddress;
  request_string += "key=";
  request_string += "Z5KAD8N8Z8GX4HHG";
  request_string += "&";
  request_string += "field1";
  request_string += "=";
  request_string += (random(1, 10));
  http.begin(request_string);
  http.GET();
  http.end();
  delay(15000);
}
