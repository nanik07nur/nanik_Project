#define LIGHT A3
#define LED 9
int BUZZER = 6;


void setup(){
  Serial.begin(9600);
  pinMode(LIGHT,INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  }

  void loop(){
    int value = analogRead(LIGHT);
    int data = map(value, 0, 1023, 255, 0 ); // map(value,fromLow,fromHigh,toLow,toHigh); chane dinamic range value coz analog
  
    Serial.print("LIGHT = ");
    Serial.print(data);
    Serial.print(", ");

    
    analogWrite(LED,value);
    Serial.print("led = ");
    Serial.println(value);
    delay(2000);

    if(data > 200){
      noTone(BUZZER);
      delay(1000);
     }
    else if(data > 100 && data < 200){
      Serial.println("BUZZER ON");
      tone(BUZZER, 400);
      delay(1000);

      noTone(BUZZER);
    }
    else {
      Serial.println("BUZZER ON");
      tone(BUZZER, 400);
      delay(1000);

      noTone(BUZZER);
    }
  }

  // map(value,fromLow,fromHigh,toLow,toHigh); chane dinamic range value

  
