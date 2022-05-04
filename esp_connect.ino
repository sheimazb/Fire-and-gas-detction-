
#include <WiFi.h>
#define SENSOR 4
const char* ssid ="AndroidTic"; //"ISIMM-etudiants";
const char* pass ="seimaticc"  ;          //"-IsImm@eTud2021-";
const char* mqtt_server = "192.168.1.3";
WiFiClient espClient;

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
/*void pub (const char* topic ,char* message) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2000) {
      lastMsg = now;
      ++value;
      client.publish(topic ,(const char*) message);
    }
  }*/
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  float sensor_volt;
  float RS_gas;
  float ratio;
  float ppm;
  float R0 = 0.43;
  char message [8];
  int sensorValue = analogRead(SENSOR);
  sensor_volt = (((float)sensorValue / 4096) * 3.3)+1.7;
  RS_gas = (3.3 - sensor_volt) / sensor_volt; 
  ratio = RS_gas / R0; // ratio = RS/R0
  ppm = (ratio - 1.3) * (-1 / 0.0003);
  //------------------------------------------------------------/
  dtostrf(ppm, 6, 2, message);
  if (!client.connected()) {
      reconnect();
    }
 

    unsigned long now = millis();
    if (now - lastMsg > 2000) {
      lastMsg = now;
      ++value;
      client.publish("test" ,message);
    }
  //pub("test",message);
  Serial.print(ratio);
  //Serial.println(ppm);
  Serial.println(message);
  delay(1000);
  /*Serial.print("sensor_volt = ");
  Serial.println(sensor_volt);
  Serial.print("RS_ratio = ");
  Serial.println(RS_gas);
  Serial.print("Rs/R0 = ");
  Serial.println(ratio);
  Serial.print("ppm = ");
  Serial.println(ppm);
  delay(1000);*/
}
