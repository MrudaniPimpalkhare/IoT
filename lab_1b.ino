#define LED 2


void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
 
}

void loop() {
  for (int i = 1000; i<6000; i+=1000){
  if (i==0) continue;
  digitalWrite(LED, HIGH);
  
  delay(2000);
  digitalWrite(LED, LOW);
  Serial.println(abs(i)/1000);
  delay(abs(i));
  if (i == 5000) {
    i = -6000;
  }
  
  }
}
