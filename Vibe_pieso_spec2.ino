#define VIB_SENSOR A0
#define TOUCH 1
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define sensor A0
#define touch 1

#define deviceID "anita0D1566783230070"
#define authnRqtNo "f8gxvioyi"
#define extrSysID "OPEN_TCP_001PTL001_1000007614"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"
#define TAG_ID "PiezoVibe"

IoTMakers g_im;

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

void setup(){
  Serial.begin(9600);
  pinMode(VIB_SENSOR,INPUT);
   init_iotmakers();
  }

  void loop(){
    //main code to run repeatedly
    int isTouch = digitalRead(VIB_SENSOR);
    int isTouch1 = analogRead(VIB_SENSOR);

   if(g_im.isServerDisconnected() == 1)
    {
      init_iotmakers();
    }
  
    if(isTouch == TOUCH){
      Serial.print("TOUCH with Analog wave = ");
      Serial.println(isTouch1);
      g_im.send_numdata(TAG_ID, (int)isTouch1);
      delay(100);
      }
   }
