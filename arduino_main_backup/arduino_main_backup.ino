/*
* @file Motor driver arduino_main.ino
*
* @date  2018-6-15
*/

// Include
#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones
#include <Wire.h>
#include <ADXL345.h>  // ADXL345 Accelerometer Library

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

int Az_move, El_move;

int tol_coarse = 15; // How off the delta angle is okay to be before we run the coarse driving program


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
int pushSpeed=100;
int elevation_min=5;
int elevation_max=85;
int DelayVar=50;           //Delay in milliseconds
int elevation_center=0;  
int azimuth_min=0;  
int azimuth_max=0;
int azimuth_center=0;
int offset_az=0;
int offset_el=0; 
int motor_direction=0; //A variable to know in which direction the motors are spinning, 1=forward elevation, 2=backward elevation, 3=forward azimuth, 4=backwward azimuth  
int safe_marg=1; 

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);             // opens serial port, sets data rate to 9600 bps
   mySerial.begin(9600); // second comport

     pinMode(roll_IN1, OUTPUT);
     pinMode(roll_IN2, OUTPUT);
     pinMode(roll_PWM, OUTPUT);

     pinMode(pitch_IN1, OUTPUT);
     pinMode(pitch_IN2, OUTPUT);
     pinMode(pitch_PWM, OUTPUT);

  //accelerometer function setup
  accelerometer_setup();
  Calibration();
  
}

void loop() {
  serialEvent();                // Goes into the serial event function and saves the data in an array 

// if everything is working and we get the right data and the right data length it will extract the AZIMUTH and ELEVATION 
  if (stringComplete == true  && errorVariable == false) {
    // HERE WE WANT TO SEND IN THE RIGHT DATA AND CREATE POINTERS 
    Extract_Datas();
    stringComplete = false;
  }
// if something is wrong with the data length it will not go to the extract datas function and instead go here  
  else if (stringComplete == true && errorVariable == true) {
    stringComplete = false;
    errorVariable = false;
   }
   //Serial.println(AZ_degree);
   //Serial.println(EL_degree);

  // Get angles for accelerometer
  getCurrentAngles();

  delta_roll = AZ_degree-rolldeg;
  delta_pitch = EL_degree-pitchdeg;

  if (delta_roll > tol_coarse || delta_pitch > tol_coarse){

    // Make a coarse adjustment of the angle
    Coarse_adjust_orientation();

    // Get angles for accelerometer
    getCurrentAngles();

    // Moving angles for motors, tune
    Tune_orientation();
  }
  else {
    // Moving angles for motors, tune
    Tune_orientation();    }
  }

