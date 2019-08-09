#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>
char auth[]="f1d37746fb17445490674971337601b3";
char ssid[]="electromodule";
char pass[]="electromodule@456";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);

}

void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();
}
