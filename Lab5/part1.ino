#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin 4
float temp;
float t_mean = 0;
float h_mean = 0;
float humidity;
DHT dht(dht_dpin, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 20; i++) {
    humidity = dht.readHumidity();
    temp = dht.readTemperature();
    // Serial.print("temperature:");
    Serial.print(temp);
    Serial.print("\t");
    // Serial.print("humidity:");
    Serial.println(humidity);
    t_mean += temp;
    h_mean += humidity;
    delay(3000);
  }
  t_mean = t_mean/20;
  h_mean = h_mean/20;
  Serial.print("tempMean:");
  Serial.print(t_mean);
  Serial.print("\t");
  Serial.print("hMean:");
  Serial.println(h_mean);

  delay(1000);
}
