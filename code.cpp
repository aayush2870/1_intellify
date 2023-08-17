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







//now the below written code is of voice assistance to turn right left or front and back







#define MOTOR_A_EN 5
#define MOTOR_A_1 6
#define MOTOR_A_2 7
#define MOTOR_B_EN 9
#define MOTOR_B_1 10
#define MOTOR_B_2 11

void setup() {
  Serial.begin(9600);
  
  pinMode(MOTOR_A_EN, OUTPUT);
  pinMode(MOTOR_A_1, OUTPUT);
  pinMode(MOTOR_A_2, OUTPUT);
  
  pinMode(MOTOR_B_EN, OUTPUT);
  pinMode(MOTOR_B_1, OUTPUT);
  pinMode(MOTOR_B_2, OUTPUT);
}

void stopMotors() {
  digitalWrite(MOTOR_A_EN, LOW);
  digitalWrite(MOTOR_B_EN, LOW);
}

void moveForward() {
  digitalWrite(MOTOR_A_1, HIGH);
  digitalWrite(MOTOR_A_2, LOW);
  digitalWrite(MOTOR_B_1, HIGH);
  digitalWrite(MOTOR_B_2, LOW);
  digitalWrite(MOTOR_A_EN, HIGH);
  digitalWrite(MOTOR_B_EN, HIGH);
}

void moveBackward() {
  digitalWrite(MOTOR_A_1, LOW);
  digitalWrite(MOTOR_A_2, HIGH);
  digitalWrite(MOTOR_B_1, LOW);
  digitalWrite(MOTOR_B_2, HIGH);
  digitalWrite(MOTOR_A_EN, HIGH);
  digitalWrite(MOTOR_B_EN, HIGH);
}

void turnRight() {
  digitalWrite(MOTOR_A_1, HIGH);
  digitalWrite(MOTOR_A_2, LOW);
  digitalWrite(MOTOR_B_1, LOW);
  digitalWrite(MOTOR_B_2, HIGH);
  digitalWrite(MOTOR_A_EN, HIGH);
  digitalWrite(MOTOR_B_EN, HIGH);
}

void turnLeft() {
  digitalWrite(MOTOR_A_1, LOW);
  digitalWrite(MOTOR_A_2, HIGH);
  digitalWrite(MOTOR_B_1, HIGH);
  digitalWrite(MOTOR_B_2, LOW);
  digitalWrite(MOTOR_A_EN, HIGH);
  digitalWrite(MOTOR_B_EN, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    stopMotors();
    delay(100);
    
    if (command == 'F') {
      moveForward();
    } else if (command == 'B') {
      moveBackward();
    } else if (command == 'R') {
      turnRight();
    } else if (command == 'L') {
      turnLeft();
    }
  }
}

// python code for assistance


import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 9600)  # Change the port as needed

def send_command(command):
    ser.write(command.encode())

try:
    while True:
        direction = input("Enter direction (F/B/R/L): ")
        if direction in ['F', 'B', 'R', 'L']:
            send_command(direction)
        else:
            print("Invalid direction! Please enter F, B, R, or L.")
except KeyboardInterrupt:
    ser.close()
    print("Serial connection closed.")


//GOOGLE MAP USAGE FOR OUR STICK

//we use the  api call by the google map api using python


import googlemaps

# Replace 'YOUR_API_KEY' with your actual Google Maps API key
API_KEY = 'YOUR_API_KEY'
gmaps = googlemaps.Client(key=API_KEY)

def get_current_location():
    # Fetch current location data (latitude and longitude)
    current_location = gmaps.geolocate()
    return current_location['location']['lat'], current_location['location']['lng']

while True:
    # Get current location
    lat, lng = get_current_location()
    print("Current Latitude:", lat)
    print("Current Longitude:", lng)
    # Further processing or interaction with the Arduino can be implemented here


// code for gsm module in aurdino 


#include <SoftwareSerial.h>

SoftwareSerial gsmModule(7, 8);  // RX, TX pins on Arduino

void setup() {
  Serial.begin(9600);
  gsmModule.begin(9600);

  // Wait till module initializes
  delay(2000);
  Serial.println("GSM Module initialized.");
}

void sendSMS(const char *message) {
  gsmModule.println("AT+CMGF=1"); // SMS mode to text
  delay(1000);

  gsmModule.print("AT+CMGS=\"989898676\""); // Replace with family phone number
  delay(1000);
  gsmModule.write(0x0D); // Send Enter
  delay(1000);

  gsmModule.print(message);
  delay(1000);
  
  gsmModule.write(0x1A); //  send of the message
  delay(1000);
}

void loop() {
  // Simulated obstacle detection condition
  bool obstacleDetected = digitalRead(2);  // Change to your actual input pin

  if (obstacleDetected) {
    sendSMS("Alert: Obstacle Detected!");
    Serial.println("SMS Sent: Obstacle Detected!");
    delay(10000); // Delay to avoid sending multiple


