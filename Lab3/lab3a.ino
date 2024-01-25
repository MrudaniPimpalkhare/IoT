
#define TRIGGER 9
#define ECHO 10
#define SPEED 0.0343
void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
}

//transimitter is connected to the trigger pin
//reciever is connected to the echo pin
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIGGER,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER,HIGH);
  /*sends out an 8 cycle sonic burst from the transmitter, which bounces of an object
  and hits the receiever*/
  
  delayMicroseconds(10); // this speeds up the simulation
  digitalWrite(TRIGGER,LOW);

  duration = pulseIn(ECHO,HIGH);
  distance = duration*(SPEED)/2; //divide by 2!
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);
  /*waits for the pin to go to that states, and starts timing it till you go to the other state*/

}
