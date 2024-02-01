const int irSensorPin = 4;
const int LED = 2;
unsigned long lastDetectionTime = 0;
const int detectionInterval = 10000;

void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, LOW);
  int irSensorValue = digitalRead(irSensorPin);
  
  while (irSensorValue == LOW) {
    

    if ((millis() - lastDetectionTime) >= detectionInterval) {
      digitalWrite(LED, HIGH);
      Serial.println("Object detected for more than 10 seconds");
      break;
    }
    irSensorValue = digitalRead(irSensorPin);
  }
 
    
    lastDetectionTime = millis();
  

  delay(1000);
}
