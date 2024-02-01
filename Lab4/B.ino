#define SENSOR_PIN 13
#define LED 2
void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int is_obstacle = digitalRead(SENSOR_PIN);
  if(is_obstacle)
  {
    Serial.println("Obstacle detected");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  else{
    Serial.println("Obstacle undetected");
    digitalWrite(LED, LOW);
  }
  delay(1000);

}

