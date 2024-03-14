#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Miami";
const char* password = "Tampa123";

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(2, OUTPUT);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  // Send HTTP GET request
  HTTPClient http;

  // Your target URL
  String url = "https://api.thingspeak.com/channels/2468586/feeds.json?api_key=7LP00LRVSJ4S6MI3&results=1";

  Serial.print("Sending HTTP GET request to: ");
  Serial.println(url);

  http.begin(url);

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode == HTTP_CODE_OK) {
      // Parse JSON
      DynamicJsonDocument doc(1024); // Adjust the size as per your JSON response
      DeserializationError error = deserializeJson(doc, http.getString());

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
      } else {
        // Extract the value of a field
        const char* fieldValue = doc["feeds"][0]["field1"];
        Serial.print("Value of your_field_name: ");
        Serial.println(fieldValue);
        if (strcmp(fieldValue, "1")==0) {
          digitalWrite(2, HIGH);
        } else digitalWrite(2, LOW);
      }
    }
  } else {
    Serial.print("Error in HTTP request: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  delay(1000); // Wait for 1 second before sending the next request
}
