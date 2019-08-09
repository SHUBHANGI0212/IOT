#include<ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
String i;
long newvar;
String httpurl;
String TheHiddenAnswerOfClient;
HTTPClient http;

String SendWithAnswer(String IPcache, String monmessagecache)
{
  httpurl = "http://";
  httpurl += IPcache;
  httpurl += monmessagecache;
  http.begin(httpurl);
  http.GET();
  TheHiddenAnswerOfClient = (http.getString());
  http.end();
  return TheHiddenAnswerOfClient;
}


void setup() {
  // put your setup code here, to run once:
  i = "";
  newvar = 0;
  Serial.begin(9600);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("Wi_Fi", "revolution");
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("Connected");
}

void loop() {
  // put your main code here, to run repeatedly:
  i = (SendWithAnswer("192.168.0.2", "YES"));
  Serial.println("Before Clear");
  Serial.println(i);
  i.remove(0, 25);
  i.remove(i.length() - 11, 11);
  Serial.println("After clear");
  Serial.println(i);
  newvar = i.toInt();
  Serial.println((2000 + newvar));
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
  client.println("</body>");
   client.println("</html>");
}
