#include <SoftwareSerial.h>
#define BT_TX 2
#define BT_RX 3
#define ledG 11
#define ledR 9
#define ledB 10

SoftwareSerial mySerial(BT_TX, BT_RX);
String myString = "";

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  while (mySerial.available()) {
    char myChar = (char)mySerial.read();
    myString += myChar;
    delay(5);
  }

  if (!myString.equals("")) {
    Serial.println("Received : " + myString);
    LED();
    myString = "";
  }
}

void LED() {
  if (myString == "R") {
    Serial.println("RED LED ON");
    analogWrite(ledR, 0);
    analogWrite(ledG, 255);
    analogWrite(ledB, 255);
  } else if (myString == "G") {
    Serial.println("GREEN LED ON");
    analogWrite(ledR, 255);
    analogWrite(ledG, 0);
    analogWrite(ledB, 255);
  } else if (myString == "B") {
    Serial.println("BLUE LED ON");
    analogWrite(ledR, 255);
    analogWrite(ledG, 255);
    analogWrite(ledB, 0);
  } 
  
  else if (myString == "AUTO") {
    Serial.println("ALL LED ON");
    analogWrite(ledR, 0);    
    analogWrite(ledG, 0);    
    analogWrite(ledB, 0);
    delay(800);
    
    analogWrite(ledR, 0);    
    analogWrite(ledG, 255);    
    analogWrite(ledB, 255);
    delay(800);

    analogWrite(ledR, 255);    
    analogWrite(ledG, 0);    
    analogWrite(ledB, 255);
    delay(800);

    analogWrite(ledR, 255);    
    analogWrite(ledG, 255);    
    analogWrite(ledB, 0);
    delay(800);   
  }
  else if (myString == "OFF") {  //LED OFF
    analogWrite(ledR, 255);    
    analogWrite(ledG, 255);    
    analogWrite(ledB, 255);
    delay(800);    
  }

  else if (myString == "ON") {  //LED ON
    analogWrite(ledR, 0);    
    analogWrite(ledG, 0);    
    analogWrite(ledB, 0);
    delay(800);    
  }
}
