#define LED_BUILTIN 2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Hello, ESP32!");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // this speeds up the simulation
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
