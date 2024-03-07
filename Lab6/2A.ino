#include <WiFi.h>
#include <WebServer.h>
#define sensor 2

WiFiServer server(80);

const char* ssid = "mruda";
const char* pwd = "12345678";
int status = WL_IDLE_STATUS;


void setup() {
  delay(500);
  Serial.begin(115200);
  // pinMode(ledPin, OUTPUT);
  pinMode(sensor, OUTPUT);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h1>Click <a href=\"/H\">here</a> turn the LED on</h1><br>");
            client.print("<h1>Click <a href=\"/L\">here</a> turn the LED off</h1><br>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(sensor, LOW);
        }
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(sensor, HIGH);
        }
      }
    }
    client.stop(); // Move this inside the if(client) block
    Serial.println("Client stopped, what will you do you loser");
    delay(5000);
  }
}
