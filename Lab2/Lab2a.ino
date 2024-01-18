// Define sensor power pin and signal pin
int sensorPowerPin = 4; // Replace X with the actual GPIO pin connected to the sensor power
int sensorSignalPin = 34; // Replace Y with the actual GPIO pin connected to the sensor signal

void setup() {
  // Begin serial communication
  Serial.begin(115200);

  // Declare sensor power pin as a digital output pin and set it to LOW
  pinMode(sensorPowerPin, OUTPUT);
  digitalWrite(sensorPowerPin, LOW);
}

void loop() {
  // Power on the water level sensor
  digitalWrite(sensorPowerPin, HIGH);
  
  // Read the sensor value using analogRead
  int sensorValue = analogRead(sensorSignalPin);
  
  // Print the value on the serial monitor
  Serial.print("Water Level: ");
  Serial.println(sensorValue);

  // Power off the water level sensor
  digitalWrite(sensorPowerPin, LOW);

  // Delay or other operations as needed
  delay(1000);
}
