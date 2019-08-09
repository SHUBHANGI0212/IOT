#include <ESP8266WiFi.h>
WiFiServer server(80);
String ClientRequest;
int ldr=A0;
int led=D1;
int relay=D0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ClientRequest = "";
pinMode(16, OUTPUT);
pinMode(5,OUTPUT);
WiFi.disconnect();
delay(3000);
Serial.println("START");
WiFi.begin("Wi_Fi","revolution");
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
     ClientRequest =(client.readStringUntil('\r'));
  client.flush();
  if (ClientRequest.indexOf("RELAY=ON")>0){
    digitalWrite(16, HIGH);
    
  }
  if (ClientRequest.indexOf("RELAY=OFF")>0){
    digitalWrite(16, LOW);
      
    }
    if (ClientRequest.indexOf("LED=ON")>0){
    digitalWrite(5, HIGH);
    
  }
  if (ClientRequest.indexOf("LED=OFF")>0){
    digitalWrite(5, LOW);
      
    }
    
   
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
  client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");

  client.println("<head>");
  client.println("<h1 style=""color:#ff0000"">");
  client.println("LED CONTROL");
  client.println("</h1>");
  client.println("</head>");
  client.println("<body>");
  client.println("<a href=");
  client.println("LED=ON");
  client.println("><button>");
  client.println("ON");
  client.println("</button></a>");
  client.println("<a href=");
  client.println("LED=OFF");
  client.println("><button>");
  client.println("OFF");
  client.println("</button></a>");
  client.println("<h1 style=""color:#ff0000"">");
  client.println("RELAY CONTROL");
  client.println("</h1>");
  client.println("<a href=");
  client.println("RELAY=ON");
  client.println("><button>");
  client.println("ON");
  client.println("</button></a>");
  client.println("<a href=");
  client.println("RELAY=OFF");
  client.println("><button>");
  client.println("OFF");
  client.println("</button></a>");
  client.println(analogRead(A0));
  client.println("</body>");

 
client.println("</html>");
Serial.println(ClientRequest);
  client.stop();
   delay(1);
  }
