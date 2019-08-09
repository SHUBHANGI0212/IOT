#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <dht.h>
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<MARQUEE><h1>IOT HOME AUTOMATION</h1></MARQUEE><br>
<p><h1>READINGS OF HUMIDITY AND TEMPERATURE</H1>

Click to turn <a href="ledOn"><BUTTON>LED ON</BUTTON></a>
Click to turn <a href="ledOff"><BUTTON>LED OFF</BUTTON></a><br>

Click to turn <a href="relayOn"><BUTTON>RELAY ON</BUTTON></a>
Click to turn <a href="relayOff"><BUTTON>RELAY OFF</BUTTON></a><br>
</center>
</body>               
</html>
)=====";


const char* ssid = "<electromodule>";
const char* password = "<electromodule@456>";
ESP8266WebServer server(80);


int ldr = A0;
int LED=16;
String page = "";
double data;
double humidity;
double temperature;
dht DHT;
#define DHT11_PIN 2
const int relayPin = D1;
void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); 
 page = "<h1> ldr reading </h1><h3> Data:</h3> <h4> " + String(data) + " </h4>" + "<h1>room temperature  </h1><h3> temperature: </h3> <h4> " + String(temperature) + " </h4>" + "<h1> room humidity </h1><h3> Humidity:</h3> <h4> " + String(humidity) + "</h4>" ;
//Send web pag 
 server.send(200, "text/html", page); 
}

void handleLEDon() { 
 Serial.println("LED on page");
 digitalWrite(LED,HIGH); //LED is connected in reverse
 server.send(200, "text/html", "LED is ON"); //Send ADC value only to client ajax request
}

void handleLEDoff() { 
 Serial.println("LED off page");
 digitalWrite(LED,LOW); //LED off
 server.send(200, "text/html", "LED is OFF");
}

void handleRelayOn()
{
  Serial.println("Relay off page");
 digitalWrite(relayPin,HIGH); //LED off
 server.send(200, "text/html", "RELAY is OFF");
 }
 void handleRelayOff() { 
 Serial.println("RELAY off page");
 digitalWrite(relayPin,LOW); //LED off
 server.send(200, "text/html", "RELAY is OFF");
}
void setup() {

  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(ldr, INPUT);
  pinMode(DHT11_PIN, INPUT);
  
pinMode(relayPin, OUTPUT);
  WiFi.begin("electromodule", "electromodule@456");
  Serial.println("start");
  pinMode(LED,OUTPUT); 
  //Power on LED state off
  digitalWrite(LED,HIGH);
  
  while (!(WiFi.status() == WL_CONNECTED))
  {
    delay(300);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP().toString());
  
   server.on("/", handleRoot);
     
  
 //Which routine to handle at root location. This is display page
  server.on("/ledOn", handleLEDon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/ledOff", handleLEDoff);
 // server.on("/read",reading);
  server.on("/relayOn",handleRelayOn);
  server.on("/relayOff",handleRelayOff);
  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:



  server.handleClient();
  data = analogRead(ldr);
  delay(1000);
  Serial.println(data);
  int chk = DHT.read11(DHT11_PIN);
  Serial.println("humidity");
  humidity = DHT.humidity;
  Serial.println(humidity, 1);
  Serial.println("Temperature");
  temperature = DHT.temperature;
  Serial.println(temperature, 1);
  delay(2000);
  
}
