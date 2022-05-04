#define SENSOR 33
void setup() {
    Serial.begin(115200);
}
 
void loop() {
    float sensor_volt;
    float RS_air; //  Get the value of RS via in a clear air
    float R0;  // Get the value of R0 via in H2
    float sensorValue;
 
  // Get a average data by testing 100 times
    for(int x = 0 ; x < 100 ; x++)
    {
        sensorValue = sensorValue + analogRead(SENSOR);
    }
    sensorValue = sensorValue/100.0;
 
 
    sensor_volt = sensorValue/1024*3.3;
    RS_air = (3.3-sensor_volt)/sensor_volt; // omit * RL
    R0 = RS_air/9.8; // The ratio of RS/R0 is 9.8 in a clear air from Graph (Found using WebPlotDigitizer)
 
    Serial.print("sensor_volt = ");
    Serial.print(sensor_volt);
    Serial.println("V");
 
    Serial.print("R0 = ");
    Serial.println(R0);
    delay(1000);
}
