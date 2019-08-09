#include <ESP8266WiFi.h>
WiFiServer server(80);
int ldr=A0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
WiFi.disconnect();
delay(3000);
Serial.println("START");
WiFi.begin("electromodule","electromodule@456");
while((!(WiFi.status() == WL_CONNECTED)))
{
  delay(300);
  Serial.print("..");
  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
WiFiClient client = server.available();
if(!client)
{
  return;
  }
  while(!client.available())
  {
    delay(1);
    }
   
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println(analogRead(A0));
client.println("</html>");
client.stop();
delay(1);
  }
