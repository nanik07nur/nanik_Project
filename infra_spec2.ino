float distance =0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int volt = map(analogRead(A0),0,1023,0,5000);
  distance =-0.0083*volt+32.315;//(27.61/(volt-0.1696))*1000;
  if(distance<0) distance=0;
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
