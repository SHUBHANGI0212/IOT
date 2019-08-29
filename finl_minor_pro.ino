#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>
#include<dht.h>
#include <SimpleTimer.h>
dht DHT;
#define DHT11_PIN 13
char auth[]="BZc0a2XTNEKVkq75yp_0xu9ezF5BeJwZ";
char ssid[]="electromodule";
char pass[]="electromodule@456";
SimpleTimer timer;
//BlynkTimer timer;
void myTimerEvent()
{
// You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, millis() / 1000);
}


BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);
}
BLYNK_READ(V1) //Blynk app has something on V5
{
int  sensorData = analogRead(A0); //reading the sensor on A0
  Blynk.virtualWrite(V1, sensorData); //sending to Blynk
}




void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);

  Serial.println("humidity and temperature detector");
 //  timer.setInterval(1000L, sendSensor);
  // timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();
timer.run();
int chk=DHT.read11(DHT11_PIN);


  if (isnan(DHT.humidity) || isnan(DHT.temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, DHT.humidity);
  Blynk.virtualWrite(V6, DHT.temperature);

Serial.println("HUMIDITY");
Serial.println(DHT.humidity,1);
Serial.println("Temperature");
Serial.println(DHT.temperature,1);
delay(2000);
}
