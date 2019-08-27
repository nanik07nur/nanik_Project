#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#include <OneWire.h>
//#include <DallasTemperature.h>
#define LIGHT A3
#define LED 9

IoTMakers g_im;

#define deviceID    "anita0D1566783230070"
#define authnRqtNo  "f8gxvioyi"
#define extrSysID   "OPEN_TCP_001PTL001_1000007614"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

#define ONE_WIRE_BUS 2

#define TAG_ID "Light"
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
 
  
  init_iotmakers();
}

void loop() {
  static unsigned long tick = millis();

  if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if((millis() - tick) > 1000)
  {
    send_data();
    tick = millis();
  }

  g_im.loop();
}

int send_data()
{
  
  int value = analogRead(LIGHT);
  int data = map(value, 0, 1023, 255, 0 ); // map(value,fromLow,fromHigh,toLow,toHigh); chane dinamic range value coz analog

  Serial.print("data : ");
  Serial.print(data);
   
  if(g_im.send_numdata(TAG_ID, (double)data) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }

  return 0;
}
