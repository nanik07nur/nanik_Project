#define VIB_SENSOR A0
#define TOUCH 1

void setup(){
  Serial.begin(9600);
  pinMode(VIB_SENSOR,INPUT);
  }

  void loop(){
    //main code to run repeatedly
    int isTouch = digitalRead(VIB_SENSOR);
    int isTouch1 = analogRead(VIB_SENSOR);
 
    if(isTouch == TOUCH){
      Serial.print("TOUCH with Analog wave = ");
      Serial.println(isTouch1);
      delay(100);
      }
   }
