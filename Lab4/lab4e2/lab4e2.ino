const int irSensorPin = 3;
const int LED = 2;
void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin, INPUT);
  pinMode(LED, OUTPUT);

}
//Connect VCC to 3.3v output, GND to gnd and out signal pin of IR to 3 (GPIO)


void loop() {
  int irSensorValue = digitalRead(irSensorPin); 

  if (irSensorValue == HIGH) {
    Serial.println("Object detected - HIGH");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);

  }
  delay(1000);
}
