#include "DHT.h"
#include <Servo.h>
#define DHTTYPE DHT11
#define dht_dpin 4
Servo servo1;
const int servoPin = 13;

float temp;
float humidity;
DHT dht(dht_dpin, DHTTYPE);
float deg2rad(float in) {
  return in * M_PI / 180.0;
}
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  dht.begin();
  servo1.attach(
    servoPin,
    0

  );
}

void loop() {
  // put your main code here, to run repeatedly:

  humidity = dht.readHumidity();
  temp = dht.readTemperature();
  float frac_t = (temp - 30) * 60;
  float frac_h = ((humidity - 48) / 32) * 180.0;
  servo1.write((frac_h));
  Serial.println((frac_h));
  Serial.print(" ");
  Serial.print(humidity);
  Serial.print(" ");
  Serial.println(temp);
  delay(1000);
}
