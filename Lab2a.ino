

#define SENSOR_POWER 36
#define SIGNAL 39
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(SENSOR_POWER, OUTPUT);
  digitalWrite(SENSOR_POWER, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(SIGNAL, HIGH);
  int value = analogRead(SIGNAL);
  Serial.println(value);
  Serial.println();
  delay(10); // this speeds up the simulation
}
