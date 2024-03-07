#include <WiFi.h>

char* ssid = "mruda";
char* password = "12345678";

WiFiServer server(80);
String header;
String output12State = "off";
int output12 = 2;

void setup() {
  Serial.begin(115200);
  pinMode(output12, OUTPUT);
  digitalWrite(output12, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            if (header.indexOf("GET /H") >= 0) {
              output12State = "on";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /L") >= 0) {
              output12State = "off";
              digitalWrite(output12, LOW);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.println("<p>Built in LED - State " + output12State + "</p>");
            if (output12State == "off") client.println("<p><a href=\"/H\"><button class=\"button\">ON</button></a></p>");
            else client.println("<p><a href=\"/L\"><button class=\"button button2\">OFF</button></a></p>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
