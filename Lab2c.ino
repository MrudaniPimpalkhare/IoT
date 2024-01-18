#define SENSOR_POWER 4
#define SENSOR_VALUE 34
#define touch_threshold 75
#define TOUCH_SIGNAL 15
#define LED 2
int required_sensor_value = 0;
void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_POWER, OUTPUT);
  digitalWrite(SENSOR_POWER, LOW);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
 
  digitalWrite(SENSOR_POWER, HIGH);
  int sensor_value = analogRead(SENSOR_VALUE);
  digitalWrite(SENSOR_POWER, LOW);

  int touch_value = touchRead(TOUCH_SIGNAL);

  if (touch_value < touch_threshold) {
    Serial.println(sensor_value);
    required_sensor_value = sensor_value;
    //Serial.println("required_sensor_value");
    Serial.print(required_sensor_value);
  }
  if (sensor_value < required_sensor_value - 20) {
    digitalWrite(LED, HIGH);
    Serial.println("Water required to be filled");
      Serial.print("Current Water Level : ");
        Serial.print(sensor_value);
    Serial.println();
  } else if (sensor_value > required_sensor_value + 20) {
    digitalWrite(LED, HIGH);
    Serial.println("Water required to be emptied");
      Serial.print("Current Water Level : ");
        Serial.print(sensor_value);
    Serial.println();
  }
  delay(5000);
}
