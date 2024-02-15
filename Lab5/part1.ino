#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin 3
float temp;
float humidity;
DHT dht(dht_dpn, DHTTYPE)

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);\
  Serial.println(F("DHTxx test!"));
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  humidity = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("temperature:")
  Serial.println(temp);
  Serial.print("humidity");
  Serial.println(humidity);
  delay(1000);


}
