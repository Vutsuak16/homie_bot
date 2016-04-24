#include "DHT.h"
#define DHTPIN 4     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
String readString;
/*
 * LDR A0
 * PIR 2
 * Motor 10
 * LED 11
 * Temp 4
 * Button 3
 */
const int ledPin=11;
const int motorPin=10;
const int pirPin = 13;
const int LDRPin = A0;
float light=9.0,motor=9.0;
long int lastTime=0;
boolean motionDetected=true;

void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(motorPin,OUTPUT);
  pinMode(LDRPin,INPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);
  Serial.begin(9600);  // initialize serial communications at 9600 bps
  attachInterrupt(digitalPinToInterrupt(3),notify,FALLING);
  attachInterrupt(digitalPinToInterrupt(2),motion,FALLING);
  dht.begin();
}

void loop()

{
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  float ldr=analogRead(LDRPin);

  if(millis()-lastTime>10*1000){
      //Serial.println((millis()-lastTime)/1000);
      motionDetected=false;
    }
  
  while (!Serial.available()) {} // wait for data to arrive
  // serial read section
  while (Serial.available())
  
  {
    if (Serial.available() >0)
    {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
      if(readString=="Light")
      {       
        light=Serial.parseFloat();
      }
      else if(readString=="Motor")
      {       
        motor=Serial.parseFloat();
      }
      
    }
  }
  
  if (readString=="Temperature")
  {  
    Serial.println(t); //see what was received
    readString="";
  }
  else if (readString=="TemperatureF")
  {  
    Serial.println(f); //see what was received
    readString="";
  }
  else if (readString=="Humidity")
  {  
    Serial.println(h); //see what was received
    readString="";
  }

  else if (readString=="LDR")
  {  
    Serial.println(ldr); //see what was received
    readString="";
  }  
  
  else if (readString=="Light")
  {  
      Serial.println("Intensity Set");
      light=map(light,0.0,9.0,0.0,255.0);
      analogWrite(ledPin,light);
      readString="";
  }
  else if (readString=="Motor")
  {  
      Serial.println("Motor Running");
      motor=map(motor,0.0,9.0,0.0,1023.0);
      analogWrite(motorPin,motor);
      readString="";
  }
 
  delay(1000);
  // serial write section
  Serial.flush();
}

void notify()
{
  Serial.println("Button");
}
void motion()
{    
    if(!motionDetected){
      Serial.println("Motion Detected");
      motionDetected=true;
      lastTime=millis();
    }
  
}
