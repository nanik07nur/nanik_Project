#define trigPin 13                 
#define echoPin 12                

#define BUZZER 6

void setup()
{
  Serial.begin (9600);       
     
  pinMode(trigPin, OUTPUT);   
  pinMode(echoPin, INPUT);   

  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  long duration, distance;                   
  digitalWrite(trigPin, LOW);                
  delayMicroseconds(2);                
  digitalWrite(trigPin, HIGH);            
  delayMicroseconds(10);               

  // (2) : Waveform length - the time from the launch
  //       of the ultrasound to the return
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);   

  distance = duration * 17 / 1000;
  if (distance >= 200 || distance <= 0)       
  {
    Serial.println("there is no obstacle");
    delay(2000);
  }
  else                                           
  {
    Serial.print(distance);                      
    Serial.println(" cm");    

    if(distance < 30)
    {
      tone(BUZZER, 400);
      delay(500);
      noTone(BUZZER);
      delay(500);
    }
    else
    {
      delay(500);
    }
  }
  
}
