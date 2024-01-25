#include "BluetoothSerial.h"
// #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
// #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
// #endif
#define TRIGGER 13
#define ECHO 14
#define SPEED 0.0343
float duration,distance;
/* Check if Bluetooth configurations are enabled in the SDK */
/* If not, then you have to recompile the SDK */

BluetoothSerial SerialBT;

void setup() {
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  
  Serial.begin(115200);
  /* If no name is given, default 'ESP32' is applied */
  /* If you want to give your own name to ESP32 Bluetooth device, then */
  /* specify the name as an argument SerialBT.begin("myESP32Bluetooth"); */
  Serial.println("hello");
  SerialBT.begin("table_39");
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop() {
  //int distance = 10;
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);  // this speeds up the simulation
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * (SPEED) / 2;  //divide by 2!
  Serial.print("Distance: ");
  Serial.println(distance);
  if (Serial.available()) {
    SerialBT.println(distance);
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(2000);
}
