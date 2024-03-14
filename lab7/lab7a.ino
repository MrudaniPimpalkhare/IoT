#include <PubSubClient.h>
#include <WiFi.h>
#include <ThingSpeak.h>
// Ensure correct credentials to connect to your WiFi Network.
char ssid[] = "Miami";
char pass[] = "Tampa123";
// Ensure that the credentials here allow you to publish and subscribe to the ThingSpeak channel.
#define channelID 2468586
const char mqttUserName[] = "DjoJLTIxCSkANBcFGhQZLzE";
const char clientID[] = "DjoJLTIxCSkANBcFGhQZLzE";
const char mqttPass[] = "NwYkickwH+LVKf1nWNP/MIHj";
// It is strongly recommended to use secure connections. However, certain hardware does not work with the WiFiClientSecure library.




#include <WiFi.h>
const char* PROGMEM thingspeak_ca_cert =
  "-----BEGIN CERTIFICATE-----\n"
  "MIIDxTCCAq2gAwIBAgIQAqxcJmoLQJuPC3nyrkYldzANBgkqhkiG9w0BAQUFADBs\n"
  "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
  "d3cuZGlnaWNlcnQuY29tMSswKQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5j\n"
  "ZSBFViBSb290IENBMB4XDTA2MTExMDAwMDAwMFoXDTMxMTExMDAwMDAwMFowbDEL\n"
  "MAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZMBcGA1UECxMQd3d3\n"
  "LmRpZ2ljZXJ0LmNvbTErMCkGA1UEAxMiRGlnaUNlcnQgSGlnaCBBc3N1cmFuY2Ug\n"
  "RVYgUm9vdCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMbM5XPm\n"
  "+9S75S0tMqbf5YE/yc0lSbZxKsPVlDRnogocsF9ppkCxxLeyj9CYpKlBWTrT3JTW\n"
  "PNt0OKRKzE0lgvdKpVMSOO7zSW1xkX5jtqumX8OkhPhPYlG++MXs2ziS4wblCJEM\n"
  "xChBVfvLWokVfnHoNb9Ncgk9vjo4UFt3MRuNs8ckRZqnrG0AFFoEt7oT61EKmEFB\n"
  "Ik5lYYeBQVCmeVyJ3hlKV9Uu5l0cUyx+mM0aBhakaHPQNAQTXKFx01p8VdteZOE3\n"
  "hzBWBOURtCmAEvF5OYiiAhF8J2a3iLd48soKqDirCmTCv2ZdlYTBoSUeh10aUAsg\n"
  "EsxBu24LUTi4S8sCAwEAAaNjMGEwDgYDVR0PAQH/BAQDAgGGMA8GA1UdEwEB/wQF\n"
  "MAMBAf8wHQYDVR0OBBYEFLE+w2kD+L9HAdSYJhoIAu9jZCvDMB8GA1UdIwQYMBaA\n"
  "FLE+w2kD+L9HAdSYJhoIAu9jZCvDMA0GCSqGSIb3DQEBBQUAA4IBAQAcGgaX3Nec\n"
  "nzyIZgYIVyHbIUf4KmeqvxgydkAQV8GK83rZEWWONfqe/EW1ntlMMUu4kehDLI6z\n"
  "eM7b41N5cdblIZQB2lWHmiRk9opmzN6cN82oNLFpmyPInngiK3BD41VHMWEZ71jF\n"
  "hS9OMPagMRYjyOfiZRYzy78aG6A9+MpeizGLYAiJLQwGXFK3xPkKmNEVX58Svnw2\n"
  "Yzi9RKR/5CYrCsSXaQ3pjOLAEFe4yHYSkVXySGnYvCoCWw9E1CAx2/S6cCZdkGCe\n"
  "vEsXCS+0yx5DaMkHJ8HSXPfqIbloEpw8nL+e/IBcm2PN7EeqJSdnoDfzAIJ9VNep\n"
  "+OkuE6N36B9K\n"
  "-----END CERTIFICATE-----\n";



#define mqttPort 1883
WiFiClient client;

const char* server = "mqtt3.thingspeak.com";
int status = WL_IDLE_STATUS;
long lastPublishMillis = 0;
int connectionDelay = 1;
int updateInterval = 15;
PubSubClient mqttClient(client);
// Function to handle messages from MQTT subscription.
void mqttSubscriptionCallback(char* topic, byte* payload, unsigned int length) {
  // Print the details of the message that was received to the serial monitor.
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Subscribe to ThingSpeak channel for updates.
void mqttSubscribe(long subChannelID) {
  String myTopic = "channels/" + String(subChannelID) + "/subscribe";
  mqttClient.subscribe(myTopic.c_str());
}

// Publish messages to a ThingSpeak channel.
void mqttPublish(long pubChannelID, String message) {
  String topicString = "channels/" + String(pubChannelID) + "/publish";
  mqttClient.publish(topicString.c_str(), message.c_str());
}
// Connect to WiFi.
void connectWifi() {
  Serial.print("Connecting to Wi-Fi...");
  // Loop until WiFi connection is successful

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {

    WiFi.begin(ssid, pass);
    delay(connectionDelay * 1000);
    Serial.print(WiFi.status());
  }
  Serial.println("Connected to Wi-Fi.");
}

// Connect to MQTT server.
void mqttConnect() {
  // Loop until connected.
  while (!mqttClient.connected()) {
    // Connect to the MQTT broker.
    if (mqttClient.connect(clientID, mqttUserName, mqttPass)) {
      Serial.print("MQTT to ");
      Serial.print(server);
      Serial.print(" at port ");
      Serial.print(mqttPort);
      Serial.println(" successful.");
    } else {
      Serial.print("MQTT connection failed, rc = ");
      // See https://pubsubclient.knolleary.net/api.html#state for the failure code explanation.
      Serial.print(mqttClient.state());
      Serial.println(" Will try again in a few seconds");
      delay(connectionDelay * 1000);
    }
  }
}
void setup() {
  Serial.begin(115200);
  // Delay to allow serial monitor to come up.
  delay(3000);
  // Connect to Wi-Fi network.
  connectWifi();
  // Configure the MQTT client
  mqttClient.setServer(server, mqttPort);
  // Set the MQTT message handler function.
  mqttClient.setCallback(mqttSubscriptionCallback);
  // Set the buffer to handle the returned JSON. NOTE: A buffer overflow of the message buffer will result in your callback not being invoked.
  mqttClient.setBufferSize(2048);
  // Use secure MQTT connections if defined.
}

void loop() {
  // Reconnect to WiFi if it gets disconnected.
  if (WiFi.status() != WL_CONNECTED) {
    connectWifi();
  }

  // Connect if MQTT client is not connected and resubscribe to channel updates.
  if (!mqttClient.connected()) {
    mqttConnect();
    mqttSubscribe(channelID);
  }

  // Call the loop to maintain connection to the server.
  mqttClient.loop();

  // Update ThingSpeak channel periodically. The update results in the message to the subscriber.
  if (abs(long(millis()) - lastPublishMillis) > updateInterval * 1000) {
    mqttPublish( channelID, (String("field1=")+String(random(300)) ));
    lastPublishMillis = millis();
  }
}