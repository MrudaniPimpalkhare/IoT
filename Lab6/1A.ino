//1A

#include <WiFi.h>
#include <WebServer.h>

char* ssid = "mruda";
char* password = "12345678";

int ledPin = 2; 
int motionSensorPin = 2; 

WebServer server(80);

String sensorData;

void setup() {
  delay(500);
  Serial.begin(115200);
  // pinMode(ledPin, OUTPUT);
  pinMode(motionSensorPin, INPUT);
  
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
  
  server.on("/", handleRoot); // Handle root URL
  server.on("/data", handleData); // Handle data URL
  
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
  
  // Update sensor data
  updateSensorData();
  
  // Add any other non-blocking code here
  delay(1000); // Example delay to avoid flooding the server with requests
}

void handleRoot() {
  // Send HTML page with JavaScript
  String page = "<h1>PIR Sensor</h1><p>Data: <span id=\"data\">" + sensorData + "</span></p>\r\n";
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
  server.send(200, "text/plain", sensorData);
}

// Function to update sensor data
void updateSensorData() {
  int motionSensorValue = digitalRead(motionSensorPin);
  if (motionSensorValue == HIGH) {
    sensorData = "Motion detected!";
    Serial.println(sensorData);
  } else {
    sensorData = "No motion detected";
    Serial.println(sensorData);
  }
}
