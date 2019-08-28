#include <Servo.h>
Servo myServo;
int angle = 0;

#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#include <OneWire.h>

IoTMakers g_im;

#define deviceID    "anita0D1566783230070"
#define authnRqtNo  "f8gxvioyi"
#define extrSysID   "OPEN_TCP_001PTL001_1000007614"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

#define ONE_WIRE_BUS 2

#define TAG_ID "Vibe"
// ************************************************************************ //

OneWire ourWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&ourWire);

void init_iotmakers()
{
  while(1)
  {
    Serial.print(F("Connect to AP..."));
    while(g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);
  
    Serial.print(F("Connect to platform..."));
    while(g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));
  
    Serial.print(F("Auth..."));
    if(g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}

void setup() {
  Serial.begin(9600);
  myServo.attach(3);
  init_iotmakers();
}

void loop() {
  // move from 0 to 180 degrees
  static unsigned long tick = millis ();
  static unsigned long tick1 =millis ();
 // double x;
  
if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  //Serial.println(tick);
  for(int i = 0; i < 10; i++) {
    for(angle = 0; angle < 180; angle++){
    
      myServo.write(angle);
      delay(20);

      tick=millis()-tick1;
      if(tick>=500){
        Serial.println(tick);
         send_data();
        tick1=millis();
      }
   }
    
    //move in reverse direction, from 180 to 0 degrees
    for(angle = 180; angle > 0; angle--)
    {
      myServo.write(angle);
      delay(20);
      tick=millis()-tick1;
      if(tick>=500){
        Serial.println(tick);
         send_data();
        tick1=millis();
    }
//    waktu=millis() - tick;
    }
  }
  g_im.loop();
}

int send_data()
{
  
  Serial.print("data : ");
  Serial.print(angle);
   
  if(g_im.send_numdata(TAG_ID, (double)angle) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }

  return 0;
}
