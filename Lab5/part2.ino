#include "DHT.h"
#include "Servo.h"
#define DHTTYPE DHT11
#define dht_dpin 3
Servo servo1;
const int servoPin = 4;

float temp;
float humidity;
DHT dht(dht_dpn, DHTTYPE)
float deg2rad(float in) {
    return in * M_PI / 180.0;
}
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  servo1.attach(
        servoPin, 
        Servo::CHANNEL_NOT_ATTACHED,
        deg2rad(2.00),
        deg2rad(179.00)
    );

}

void loop() {
  // put your main code here, to run repeatedly:
  humidity = dht.readHumidity();
  temp = dht.readTemperature();
  float frac_t = (temp-30)/(3*180.0);
  float frac_h = (humidity-42)/(32*180.0);
  servo1.write(deg2rad(frac_h));
  Serial.println(deg2rad(frac_h));
  delay(1000);
    

}
