#define SENSOR_PIN 13

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int is_obstacle = digitalRead(SENSOR_PIN);
  if(is_obstacle)
  {
    Serial.println("Obstacle detected");
  }
  else{
    Serial.println("Obstacle undetected");
  }
  delay(5000);

}
