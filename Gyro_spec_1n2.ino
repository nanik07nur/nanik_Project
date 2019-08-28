#include <Wire.h>
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define deviceID "anita0D1566783230070"
#define authnRqtNo "f8gxvioyi"
#define extrSysID "OPEN_TCP_001PTL001_1000007614"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"
#define TAG_ID "Temperatur"

const int MPU = 0x68;
int16_t acx, acy, acz, tmp, gyx, gyy, gyz;
double tx,t,tf;

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0xF8);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0xF8);
  Wire.endTransmission(true);
   init_iotmakers();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

   if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  acx = Wire.read() << 8 | Wire.read();
  acy = Wire.read() << 8 | Wire.read();
  acz = Wire.read() << 8 | Wire.read();   
  tmp = Wire.read() << 8 | Wire.read();
  gyx = Wire.read() << 8 | Wire.read();
  gyy = Wire.read() << 8 | Wire.read();
  gyz = Wire.read() << 8 | Wire.read();

  int xaxis = (acx - 1090);
  int yaxis = (acy - 930);
  int zaxis = (acz - 1000);

  //gyro correction
  int GyX = 480;
  int GyY = 170;
  int GyZ = 210;

  //temperature correction
  tmp=tmp/16;

   g_im.send_numdata(TAG_ID, (int)tmp);
  
  Serial.print("xaxis : ");
  Serial.print(xaxis);
  Serial.println();
  Serial.print("yaxis : ");
  Serial.print(yaxis);
  Serial.println();
  Serial.print("zaxis : ");
  Serial.print(zaxis);
  Serial.println();

  //Measure Value
  Serial.print("temp : ");
  Serial.print(tmp);
  Serial.println();
  Serial.print("G Y axis : ");
  Serial.print(gyy+GyX);
  Serial.println();
  Serial.print("G X axis : ");
  Serial.print(gyx+GyY);
  Serial.println();
  Serial.print("G Z axis : ");
  Serial.print(gyz+GyZ);
  Serial.println();
  Serial.println();
  delay(1000);
  g_im.loop(); 
}
