#define trigpin 2 // digital pin 2
#define echopin 3 // digital pin 3
#define buzzer 12

#define trigpin1 4 // digital pin 2
#define echopin1 5 // digital pin 3

const int PIR_Sensor = 6;     // the number of the PIR_Sensor pin
const  int ledPin =  13;      // the number of the LED pin
int Motion_State = 0;         //  variable for reading the Motion status
#define buzzer1 11

#include "Wire.h"      
#include "I2Cdev.h"    
#include "MPU6050.h"    
#define bz 7
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

void setup()
{
  digitalWrite(buzzer, LOW);
Serial.begin(9600);
pinMode(trigpin, OUTPUT);
pinMode(echopin, INPUT);
pinMode(buzzer, OUTPUT);

  pinMode(trigpin1, OUTPUT);
pinMode(echopin1, INPUT);

  pinMode(ledPin,  OUTPUT);    // initialize the LED pin as an output:
  pinMode(PIR_Sensor, INPUT);
  //Serial.begin(9600); // initialize the PIR_Sensor pin as an input:
  pinMode(buzzer1, OUTPUT);

   Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  pinMode(bz, OUTPUT);
}

void loop()
{
  //Code for obstacle
int duration, distance;
  digitalWrite(trigpin, HIGH);
delayMicroseconds(1000);  
digitalWrite(trigpin, LOW);
duration = pulseIn(echopin,HIGH);
distance = ( duration / 2) / 29.1;
if ( distance < 0 )
{
  Serial.println("out of Range");
}

if ( (distance >= 0) && (distance <= 30 ))
{
  //digitalWrite(buzzer, HIGH);
      tone(buzzer,261);
}

if (distance > 30 )
{
  //digitalWrite(buzzer, LOW);
      noTone(buzzer);
}
//  Serial.println();
Serial.print(distance);
Serial.print("  - Obstacle Centimeters\n");

//Code for depth
int duration1, distance1;
  digitalWrite(trigpin1, HIGH);
delayMicroseconds(1000);  
digitalWrite(trigpin1, LOW);
duration1 = pulseIn(echopin1,HIGH);
distance1 = ( duration1 / 2) / 29.1;
if ( distance1 < 0 )
{
  Serial.println("out of Range");
}

if ( (distance1 >= 0) && (distance1 <= 10 ))
{
  //digitalWrite(buzzer, HIGH);
      tone(buzzer,261);
}

if (distance1 > 10 )
{
  //digitalWrite(buzzer, LOW);
      noTone(buzzer);
}
//  Serial.println();
Serial.print(distance1);
Serial.print("  - Depth Centimeters\n");

//Motion
Motion_State = digitalRead(PIR_Sensor);  // read the state of the PIR_Sensor value:
  if (Motion_State == HIGH) {   // check if the Motion_State is High.
  Serial.println(Motion_State);
  digitalWrite(ledPin,  HIGH); // turn LED on:
  //digitalWrite(buzzer1, HIGH);
  //delay(100);
  //tone(buzzer1,HIGH);
  } else {
   
    digitalWrite(ledPin,  LOW);
    Serial.println(Motion_State);  // turn LED off:
    //digitalWrite(buzzer1, LOW);
    //noTone(buzzer1);
  }

//Rain
int anaval = analogRead(A0);
Serial.println(anaval);
if(anaval < 1000)
{
  //analogWrite(buzzer, 50);
  //digitalWrite(buzzer1,HIGH);
  tone(buzzer1,349);
  Serial.println("It's Raining");
}
else
{
  noTone(buzzer1);
  //digitalWrite(buzzer1,LOW);
  //analogWrite(buzzer, 0);
  Serial.println("Not Raining");
}
delay(1000);

mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);
  data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
  delay(500);
  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("Axis Z  = ");
  Serial.println(data.Z);


//if((data.X >159 && data.X < 169 ) && (data.Y > 74 && data.Y < 81) && (data.Z > 244 && data.Z < 251))
//{
  //Serial.print("Stable");
  //digitalWrite(bz,LOW);
//}
if ((data.Y > 145 && data.Y < 249 ) || (data.Y > 0 && data.Y < 50))
{
  Serial.print("Unstable");
  digitalWrite(bz,HIGH);
}
else if ((data.X >0 && data.X < 100 ) || (data.X > 200 && data.X < 250))

{
  Serial.print("Unstable");
  digitalWrite(bz,HIGH);
}
else
{
digitalWrite(bz,LOW);
}


}