//1A

#include <WiFi.h>
#include <WebServer.h>
#include<Arduino.h>
#define SPEED 0.0343

char* ssid = "mruda";
char* password = "12345678";

int ledPin = 2;
int irsensor = 2;
int trigger = 13;
int echo = 14;



WebServer server(80);

String sensorData;
int count = 0;
// float prev_dist = 0;

void setup() {
  delay(500);
  Serial.begin(115200);
  // pinMode(ledPin, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(irsensor, INPUT);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);      // Handle root URL
  server.on("/data", handleData);  // Handle data URL

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();

  // Update sensor data
  // updateSensorData();
  IRData();


  // Add any other non-blocking code here
  delay(1000);  // Example delay to avoid flooding the server with requests
}

void handleRoot() {
  // Send HTML page with JavaScript
  String page = "<h1>PIR Sensor</h1><p>Data: <span id=\"data\">" + String(count) + "</span></p>\r\n";
  page += "<script>\r\n";
  page += "var x = setInterval(function() {loadData(\"/data\", updateData)}, 1000);\r\n";
  page += "function loadData(url, callback){\r\n";
  page += "var xhttp = new XMLHttpRequest();\r\n";
  page += "xhttp.onreadystatechange = function(){\r\n";
  page += "if(this.readyState == 4 && this.status == 200){\r\n";
  page += "callback.apply(xhttp);\r\n";
  page += "}\r\n";
  page += "};\r\n";
  page += "xhttp.open(\"GET\", url, true);\r\n";
  page += "xhttp.send();\r\n";
  page += "}\r\n";
  page += "function updateData(){\r\n";
  page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
  page += "}\r\n";
  page += "</script>\r\n";
  server.send(200, "text/html", page);
}

void handleData() {
  // Send sensor data as the response
  server.send(200, "text/plain", String(count));
}

// Function to update sensor data
// void updateSensorData() {
//   int motionSensorValue = digitalRead(motionSensorPin);
//   if (motionSensorValue == HIGH) {
//     sensorData = "Motion detected!";
//     Serial.println(sensorData);
//   } else {
//     sensorData = "No motion detected";
//     Serial.println(sensorData);
//   }
// }

float readDist() {

  Serial.println("calculating distance:");
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  float duration = pulseIn(echo, HIGH);
  float distance = duration * SPEED / 2;
  return distance;
}


void IRData() {

  Serial.println("IR values...");
  int val = digitalRead(irsensor);
  if (val) {
    Serial.println("detected motion");
    float prev_dist = readDist();
    Serial.println("prev distance =" + String(prev_dist));
    delay(1000);
    float dist = readDist();
    Serial.println("curr distance =" + String(dist));
    if(prev_dist<dist && count>0)
    {
      count--;
    }else if(prev_dist>dist){
      count++;
    }else{
      Serial.println("move idiot");
    }
    Serial.println(count);
  }else{
    Serial.println("low");
  }
}
