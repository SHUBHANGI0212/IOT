#include<ESP8266WiFi.h>

WiFiClient client;
String thingspeakAddress[] = "api.thingspeak.com";
String thingtweetAPIKey="916OAGI8LOTEDXS6";
String tsData;
int ldr=A0;
int val;
int value;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ldr,INPUT);
  WiFi.disconnect();
  delay(3000);
Serial.println("START");
WiFi.begin("Wi_Fi","revolution");
while((!(WiFi.status() == WL_CONNECTED)))
{
  delay(300);
  Serial.print("...");
  }
  Serial.println("CONNECTED");

Serial.println("YOUR IP IS");
Serial.println((WiFi.localIP().toString()));
}

void loop() {
  // put your main code here, to run repeatedly:
   val=analogRead(ldr);
value=map(val,0,1023,0,100);
 Serial.println(value);
if(value>=80)
{
 
  if(client.connect("api.thingspeak.com",80)){

  tsData = "api_key=";
  tsData+=thingtweetAPIKey;
  tsData+="&status=";
  tsData +="ldr reading...";
  client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("Content-: application/x-www-form-urlecoded\n");
  client.print("Content-Length: ");
  client.print(tsData.length());
  client.print("\n\n");
  client.print(tsData);
 
}
else
{
  if(client.connect("api.thingspeak.com",80)){

  tsData = "api_key=";
  tsData+=thingtweetAPIKey;
  tsData+="&status=";
  tsData += "Value of ldr is less than 80 ";
  client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("Content-Type: application/x-www-form-urlecoded\n");
  client.print("Content-Length: ");
  client.print(tsData.length());
  client.print("\n\n");
  client.print(tsData);
  
  }
}
}
}
