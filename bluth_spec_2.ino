//use BLUETOOTH module HC10 
//type this comment in serial module
    //1. AT ==> Test Command or Disconnect Command. If the module is not connected to a remote device it will reply: “OK”. || If the module has a connection then the connection will be closed. If the notification setting is active, the module will reply with “OK+LOST”
    //2. AT+NAME**** ==> to give a name your device  (**** = your propose name)
    //3. AT+PASS****** ==> to give a password your device  (6 digits )
    //4. AT+ROLE? ==> T+ROLE? returns either 0 or 1.|| 0 = Slave or Peripheral , 1 = Master or Central. The default setting is 0 (Slave).
    //5. AT+ROLEx ==> Set the device role. x is 0 or 1. To change to Slave/Peripheral mode use AT+ROLE0. This will return OK+Set:0 || To change to Master/Central mode use AT+ROLE1. This will return OK+Set:1 || AT+ROLEx mat require a reset before the changes take place.
    //6. AT+IMMEx ==> Set the start up mode. AT+IMME0 sets auto connect on start* || AT+IMMEx mat require a reset before the changes take place.
    //7. AT+RESET ==> Restarts the module
    //8. AT+RENEW ==> Resets the module to the factory settings
    
#include <SoftwareSerial.h>
#define BT_TX 2
#define BT_RX 3

SoftwareSerial mySerial(BT_TX, BT_RX);

void setup(){
  Serial.begin(9600);
  Serial.println("ENTER AT Commands:");
  mySerial.begin(9600);

}

void loop(){
  if(mySerial.available()){
    Serial.write(mySerial.read());
    }
    if(Serial.available()){
      delay(5);
      mySerial.write(Serial.read());
    }
}
