#define LED_BUILTIN 2
int freq;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  while (Serial.available() == 0)
  {
  }

  freq = Serial.parseInt();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println(freq);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("HIGH");
  delay(freq*1000); // this speeds up the simulation
  digitalWrite(LED_BUILTIN,LOW);
  Serial.println("LOW");
  delay(freq*1000);
}
