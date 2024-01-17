#define POWER 36
#define LED_BUILTIN 4
#define SIGNAL 39
#define THRESHOLD
#define TOUCH 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(POWER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(POWER, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Hello, ESP32!");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(POWER, HIGH);
  int value = analogRead(SIGNAL);
  digitalWrite(POWER, LOW);
  int touch = touchRead();
  if (touch)
  {
    value = analogRead(SIGNAL);
    if (value >= THRESHOLD)
    {
      Serial.println("Blah Blah\n");
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }

  delay(10); // this speeds up the simulation
}
