#include <dht.h>
#define sensor 6

#define RELAY A0

dht DHT ;

int trig = 7; 
int echo = 8;
int durasi, jarak;

void setup() { 
  Serial.begin(115200);  
  Serial1.begin(115200);  
  
  pinMode(trig, OUTPUT);  
  pinMode(echo, INPUT);
  pinMode(RELAY, OUTPUT);
}

void loop() { 
  DHT.read11(sensor);
  float suhu = DHT.temperature;
  float lembab = DHT.humidity;
  
  Serial.print("Temperature = ");
  Serial.println(suhu);
  Serial1.print("Temperature = ");
  Serial1.println(suhu);
  Serial.print("Humidity = ");
  Serial.println(lembab);
  Serial1.print("Humidity = ");
  Serial1.println(lembab);
  
  digitalWrite(trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);  
  durasi= pulseIn(echo, HIGH); 
  jarak= (durasi/2)/29.1 ;
  
  Serial.print("Jarak = "); 
  Serial.print(jarak);
  Serial.println(" cm");
  Serial1.print("Jarak = ");
  Serial1.print(jarak);
  Serial1.println(" cm");
  
  if(jarak<50 || suhu >33){
    Serial.println("Kipas ON");
    digitalWrite(RELAY,LOW);
  }
  else{
    Serial.println("Kipas OFF");
    digitalWrite(RELAY,HIGH);
  }
  delay(5000);
}
