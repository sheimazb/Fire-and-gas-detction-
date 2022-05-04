#include <SoftwareSerial.h> 
#include <TinyGPS.h> 
float lat ;
float lon ; 
SoftwareSerial gpsSerial(3,4);//rx,tx 
TinyGPS gps; // create gps object 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // connect serial 
//Serial.println("The GPS Received Signal:"); 
gpsSerial.begin(9600); // connect gps sensor 
}
void loop(){

while(gpsSerial.available()){ // check for gps data 
  if(gps.encode(gpsSerial.read()))// encode gps data 
  {  
  gps.f_get_position(&lat,&lon); // get latitude and longitude 
 

  Serial.print("Position: "); 
  Serial.print("Latitude:"); 
  Serial.print(lat,6); 
  Serial.print(";"); 
  Serial.print("Longitude:"); 
  Serial.println(lon,6);  
 
  Serial.print(lat); 
  Serial.print(" "); 
 
 } 
} 
String latitude = String(lat,6); 
  String longitude = String(lon,6); 
Serial.println("laltitude : "+latitude+";"+ "longitude : "+longitude); 
delay(1000); 
} 
