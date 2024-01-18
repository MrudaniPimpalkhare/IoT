#define LED 2
#define TOUCH 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = touchRead(TOUCH);
  //code for threshold
  delay(10); // this speeds up the simulation
}
