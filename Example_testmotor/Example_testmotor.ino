/*************************************************************
Motor Shield 1-Channel DC Motor Demo
by Randy Sarafan

For more information see:
https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/
#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones
#include <Wire.h>
#include <ADXL345.h>  // ADXL345 Accelerometer Library
#include <Time.h>
SoftwareSerial mySerial(10,11);   //RX, TX

// Define variables
String inputString = "";            // String to save the input in 
boolean stringComplete = false;     // used to determine when the string is complete
const byte numChars = 28;           // just to have a maximum of chars (normally 23 + extra zero)
char receivedChars[numChars];       // array of chars to store the values in
int Az_0, Az_End;                   // Aximuth, refering to the index in the string that you get, the first interesting number and the last
int El_0, El_End;                   // Elevation, refering to the index in the string that you get, the first interesting number and the last
int AZ_degree, EL_degree;           // The values to be sent to the motors
boolean errorVariable = false;      // error vaiable

ADXL345 acc; //variable adxl is an instance of the ADXL345 library
int ax,ay,az;  
int rawX, rawY, rawZ;
float X, Y, Z;
float rollrad, pitchrad;
float rolldeg, pitchdeg;
float aoffsetX, aoffsetY, aoffsetZ;
float delta_roll, delta_pitch;

// Define pins for motorcontroller
const int sensor_Pin_1 = A0; //Microswitches 
const int sensor_Pin_2 = A1; //Microswitches   
const int roll_IN1=13;//12;      //Direction for motor conneced to channel A
const int roll_IN2=8;//9;       //Break
const int roll_PWM=11;//3;       //PWM, velocity for A

const int pitch_IN1=12;//13;     //Direction for motor conneced to channel B
const int pitch_IN2=9;//8;      //Break
const int pitch_PWM=3;//11;     //PWM, velocity for B
int sensorValue_1=0;        //         
int sensorValue_2=0;        //
int setupSpeed=100;         //Speed between 0-255
int elevation_min=5;
int elevation_max=85;
int DelayVar=50;           //Delay in milliseconds
int elevation_center=0;  
int azimuth_min=0;  
int azimuth_max=0;
int azimuth_center=0;
int offset_az=0;
int offset_el=0;   
int sensorPin = A0;
int ledPin=13;
int sensorValue = 0;


void setup() {
  int i=0;
    }
  /*Pitch_Brake();  
  delay(2000);
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  Serial.begin(9600); 
  pinMode(pitch_PWM,OUTPUT);    // set the pin to input
  */
}

void loop(){

  /*  //forward @ full speed

  //pinmode(14,input);                       // set the pin to input
  sensorValue = digitalRead(sensorPin);        // read analog pin 0 as digital and set it to a variable
  Serial.println(sensorValue);
  
  
  if (sensorValue == HIGH){                   // it shows pressed
     //delay(5000); 
     Pitch_Positive(100);
     delay(500);
     //digitalWrite(12,LOW); //Establishes forward direction of Channel A
     //digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
     //analogWrite(3, 255);   //Spins the motor on Channel A at full speed
    //Serial.println("motor");
   }
 else if (sensorValue == LOW){
    Pitch_Brake();   //engage the Brake for Channel A
  }
   // Serial.println("do it again");  
    //}             // it shows not pressed )
    */
}
