const int irSensorPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin, INPUT);
}

void loop() {
  int irSensorValue = digitalRead(irSensorPin); 

  if (irSensorValue == HIGH) {
    Serial.println("Object detected - HIGH");
  } else {
    Serial.println("Not detected - LOW");
  }

  delay(5000);
}
