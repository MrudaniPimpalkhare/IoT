const int irSensorPin = 3;
const int LED = 2;
unsigned long lastDetectionTime = 0;
const int detectionInterval = 10000;

void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  int irSensorValue = digitalRead(irSensorPin);

  if (irSensorValue == HIGH) {
    Serial.println("Object detected - HIGH");

    if ((millis() - lastDetectionTime) >= detectionInterval) {
      digitalWrite(LED, HIGH);
      Serial.println("Object detected for more than 10 seconds");
    } else {
      digitalWrite(LED, LOW);
    }

    lastDetectionTime = millis();
  } else {
    digitalWrite(LED, LOW);
  }

  delay(1000);
}
