/*
* @file Motor driver arduino_main.ino
*
* @date  2018-6-15
*/

// #########################################
// INCLUDE LIBARIES
#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones
#include <Wire.h>
#include <ADXL345.h>  // ADXL345 Accelerometer Library
// #########################################

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

// ##############################################
// Define varibales to acceleromter
ADXL345 acc; //variable adxl is an instance of the ADXL345 library
int ax,ay,az;  
int rawX, rawY, rawZ;
float X, Y, Z;
float rollrad, pitchrad;
float rolldeg, pitchdeg;
float aoffsetX, aoffsetY, aoffsetZ;
float delta_roll, delta_pitch;

// ################################################

int Az_move, El_move;



// #################################################
// DEFINE PINS FOR MICROCONTROLLER
// Microswitches 
const int sensor_el = A2;        // Switch for elevtion
const int sensor_az = A3;        // Switch for azimuth

// Motor 1
const int roll_IN1=7;            // Motor pin A1, positive
const int roll_IN2=8;            // Motor pin B1, positive
const int roll_PWM=5;            // PWM, "velocity"

// Motor 2
const int pitch_IN1=4;          // Motor pin A2, positive
const int pitch_IN2=9;          // Motor pin B2, negative
const int pitch_PWM=6;          // PWM, "velocity"

// #################################################

int sensorValue_1=0;        //         
int sensorValue_2=0;        //
int pushSpeed=100;

// LOCATION OF SWITCHES (MIGHT WANNA DO LOCAL?!)
int elevation_min=5;       // Elevation lower switch
int elevation_max=85;      // Elevation upper switch
  

int DelayVar=50;           //Delay in milliseconds  
int azimuth_min=0;  
int azimuth_max=0;

// Motor offset (from accelerometer)
int offset_az=0;
int offset_el=0; 

// Which direction are we driving
int motor_direction=0; // 1=forward elevation, 2=backward elevation, 3=forward azimuth, 4=backwward azimuth  

// ##############################################
// MOTOR SPEED
//int fastSpeed = 200; 
//int slowSpeed = 100;
int setupSpeed=250;         //Speed between 0-255 // The motor speed in calibration and accelerometer_setup

// ##############################################
// OTHER 
int tol_coarse = 15; // How off the delta angle is okay to be before we run the coarse driving program

// ##############################################
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);             // opens serial port, sets data rate to 9600 bps
   mySerial.begin(9600);           // second comport
   
   pinMode(sensor_el, INPUT);      // Set switch elevation as an input
   pinMode(sensor_az, INPUT);      // Set switch azimuth as an input

  //accelerometer function setup
  accelerometer_setup();
  Calibration();

  // Setting Satelite values, first time, wait for input (TESTING!)
  WriteSateliteAnglesFirst;

}

void loop() {
      // I DONT THINK WE WILL EVER GET HERE CUZ WE CHECK THIS WHILE RUNNING THE MOTORS (in delay)
      // If a switch is activated, run switch protocol
      if ((sensor_el==HIGH) || (sensor_az==HIGH)){
      End_switches();
      }
  
    // Update the satelite angles from WX-track and make an convertion 
    //UpdateSateliteAngles();
    WriteSateliteAngles();
  
    // Get angles for accelerometer
    getCurrentAngles();

    // Get the delta angle between motor position and satelite position
    delta_roll = AZ_degree-rolldeg;                     // [degree]
    delta_pitch = EL_degree-pitchdeg;                   // [degree]

    // Do a coarse adjustment of the angles if the delta angle is large
    if (delta_roll > tol_coarse || delta_pitch > tol_coarse){
  
      // Make a coarse adjustment of the angle
      Coarse_adjust_orientation();
  
      // Get angles for accelerometer
      getCurrentAngles();
  
      // Moving angles for motors, tune
      Tune_orientation();
    }

    // Do a fine adjustment of the angles, if the delta angle is pretty small
    else {
      // Moving angles for motors, tune
      Tune_orientation();    
      }


}
   
