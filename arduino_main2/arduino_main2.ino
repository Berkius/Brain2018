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
#include <ITG3200.h>  // ITG3200 Gyro libary
// #########################################

SoftwareSerial mySerial(10,11);   //RX (green), TX (white)
// #########################################
// DEFINE VARIBALES RELATED TO EXTRACTING SATELITE COORDS FROM WX-TRACK
boolean stringComplete = false;     // used to determine when the string is complete
const byte numChars = 28;           // just to have a maximum of chars (normally 23 + extra zero)
char receivedChars[numChars];       // array of chars to store the values in
int AZ_degree, EL_degree;           // The values to be sent to the motors
boolean errorVariable = false;      // error vaiable

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

// ##############################################
// Define varibales to acceleromter
ADXL345 acc;                            //variable adxl is an instance of the ADXL345 library

int ax,ay,az;                           // Accelerometer values, used in getCurrentPitch and accelerometer_setup

float rolldeg, pitchdeg;                         // The angle of the motors [degree]
float aoffsetX, aoffsetY, aoffsetZ;     // ??
float delta_roll, delta_pitch;          // The offset between the aceelerometer value and the actual value (from switch) [degree]

// Motor offset (from accelerometer)
float offset_el=0;                      //The elevation offset measured from the elevation switch
int switch_count_az=0;                  //Count number of laps the parabola have turned in a specific direction 

// Define varibales to gyroscope
ITG3200 gyro = ITG3200();
float gx, gy, gz;                       // 

// ##############################################
// MOTOR SPEED
int fastSpeed = 255;          // Full speed
int slowSpeed = 100;        // 

// ##############################################
// OTHER 
int tol_coarse = 15; // How off the delta angle is okay to be before we run the coarse driving program

// Location of switches
int azimuth_min=5;         // Azimuth left switch
int azimuth_max=355;       // Azimuth right switch
int elevation_min=5;       // Elevation lower switch
int elevation_max=85;      // Elevation upper switch

// Which direction are we driving
int motor_direction=0; // 1=forward elevation, 2=backward elevation, 3=forward azimuth, 4=backwward azimuth  

int PITCH_T = 90;
int ROLL_T = 90;

// ##############################################

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);             // opens serial port, sets data rate to 9600 bps
   mySerial.begin(9600);           // second comport
   
   pinMode(sensor_el, INPUT);      // Set switch elevation as an input
   pinMode(sensor_az, INPUT);      // Set switch azimuth as an input

  //accelerometer function setup
  accelerometer_setup();

  // Setup gyroscope 
  Serial.print("Gyro setup..     ");
  gyro.init(ITG3200_ADDR_AD0_LOW);
  gyro.zeroCalibrate(2500, 2);    // 2 sample 2500 ms/sample
  Serial.println("Gyro setup done");
  
  Calibration();
}

void loop() {

    // Update the satelite angles from WX-track and make an convertion 
    UpdateSateliteAngles();
    //WriteSateliteAngles();
  
    // Get angles for accelerometer
    getCurrentPitch();

    // Get the delta angle between motor position and satelite position
    //delta_roll = AZ_degree-rolldeg;                     // [degree]
    delta_pitch = EL_degree-pitchdeg;                   // [degree]

    // Do a coarse adjustment of the angles if the delta angle is large
    if (abs(delta_roll) > tol_coarse || abs(delta_pitch) > tol_coarse){
  
      // Make a coarse adjustment of the angle
      //Coarse_adjust_orientation();
      Serial.print("Skipping coarse");
  
      // Get angles for accelerometer
      getCurrentPitch();
  
      // Moving angles for motors, tune
      Tune_orientation();
    }

    // Do a fine adjustment of the angles, if the delta angle is pretty small
    else {
      // Moving angles for motors, tune
      Tune_orientation();    
      }


}
   
