#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
#include <dht.h>
#define sensor D1
dht DHT ;
int trig = D2; 
int echo = D3;
int durasi, jarak;
//-------- Customise these values -----------
const char* ssid = "[SSID_NAME]";
const char* password = "[SSID_PASSWORD]";


#define ORG "6hwdst"
#define DEVICE_TYPE "kpsangin"
#define DEVICE_ID "kpsangin"
#define TOKEN "qwerty1234"
//-------- Customise the above values --------

char server[] = ORG".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);
void setup() { 
  Serial.begin(115200);  
  pinMode(trig, OUTPUT);  
  pinMode(echo, INPUT);
  while(!Serial){
    
    } 
    Serial.print("Connecting to "); 
    Serial.print(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print("."); 
    }
    Serial.println("");
       
    Serial.print("WiFi connected, IP address: ");
    Serial.println(WiFi.localIP()); 
}

void loop() { 
  DHT.read11(sensor);
  float suhu = DHT.temperature;
  float lembab = DHT.humidity;
  
  digitalWrite(trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);  
  durasi= pulseIn(echo, HIGH); 
  jarak= (durasi/2)/29.1 ;
  
  if (!client.connected()) {
    Serial.print("Reconnecting client to ");
    Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
  }
 
  if(Serial.available()){
    Serial.write(Serial.read());
    
    String payload = "{\"kelompok7\":{\"Name\":\" Kipas Angin Otomatis\"";
    payload += ",\"Temperature\":";
    payload += suhu;
    payload += ",\"Humidity\":";
    payload += lembab;
    payload += ",\"Jarak\":";
    payload += jarak;
    payload += "}}";
 
    Serial.print("Sending payload: ");
    Serial.println(payload);
 
    if (client.publish(topic, (char*) payload.c_str())) {
       Serial.println("Publish ok");
    }
    else {
       Serial.println("Publish failed");
    }
    delay(5000);
   }
}
