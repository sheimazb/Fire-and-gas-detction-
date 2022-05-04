/*!
 * @file  SIM808_SendSMS.ino
 * @brief  Send SMS messages
 * @details  1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's send SMS func.
 * @n        2. Open the SIM808_SendSMS example or copy these code to your project
 * @n        3. Replace the phoneNumber：#define PHONE_NUMBER  "187******39"
 * @n        4. Download and dial the function switch to Arduino, and enjoy it
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [Jason](jason.ling@dfrobot.com)
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-02-08
 * @url  https://github.com/DFRobot/DFRobot_SIM808
 */
#include <DFRobot_SIM808.h>

#include "HardwareSerial.h"
#define PIN_RX 11
#define PIN_TX 10
SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

void setup() {
mySerial.begin(9600);
Serial.begin(9600);

//************* Turn on the GPS power************
if( sim808.attachGPS())
Serial.println("Open the GPS power success");
else
Serial.println("Open the GPS power failure");

}

void loop() {
//************** Get GPS data *******************
if (sim808.getGPS()) {
Serial.print(sim808.GPSdata.year);
Serial.print("/");
Serial.print(sim808.GPSdata.month);
Serial.print("/");
Serial.print(sim808.GPSdata.day);
Serial.print(" ");
Serial.print(sim808.GPSdata.hour);
Serial.print(":");
Serial.print(sim808.GPSdata.minute);
Serial.print(":");
Serial.print(sim808.GPSdata.second);
Serial.print(":");
Serial.println(sim808.GPSdata.centisecond);

Serial.print("latitude :");
Serial.println(sim808.GPSdata.lat,6);

sim808.latitudeConverToDMS();
Serial.print("latitude :");
Serial.print(sim808.latDMS.degrees);
Serial.print("\^");
Serial.print(sim808.latDMS.minutes);
Serial.print("\'");
Serial.print(sim808.latDMS.seconeds,6);
Serial.println("\"");
Serial.print("longitude :");
Serial.println(sim808.GPSdata.lon,6);
sim808.LongitudeConverToDMS();
Serial.print("longitude :");
Serial.print(sim808.longDMS.degrees);
Serial.print("\^");
Serial.print(sim808.longDMS.minutes);
Serial.print("\'");
Serial.print(sim808.longDMS.seconeds,6);
Serial.println("\"");

Serial.print("speed_kph :");
Serial.println(sim808.GPSdata.speed_kph);
Serial.print("heading :");
Serial.println(sim808.GPSdata.heading);

//************* Turn off the GPS power ************
sim808.detachGPS();
}

}
