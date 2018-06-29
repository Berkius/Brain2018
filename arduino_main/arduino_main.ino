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

SoftwareSerial mySerial(10,11);   //RX (green), TX (white) (WX track)
// #########################################
// DEFINE VARIBALES RELATED TO EXTRACTING SATELITE COORDS FROM WX-TRACK
boolean stringComplete = false;     // used to determine when the string is complete
char receivedChars[28];       // array of chars to store the values in
int AZ_degree, EL_degree;           // The values to be sent to the motors
boolean errorVariable = false;      // error vaiable   RETURN FROM SERIAL EVENT

// #################################################
// DEFINE PINS FOR MICROCONTROLLER
// Microswitches 
const int sensor_el = A2;         // Switch for elevtion
const int sensor_az = A3;         // Switch for azimuth

// Motor 1
const int roll_IN1=7;            // Motor pin A1, positive
const int roll_IN2=8;            // Motor pin B1, positive
const int roll_PWM=5;            // PWM, "velocity"

// Motor 2
const int pitch_IN1=4;           // Motor pin A2, positive
const int pitch_IN2=9;           // Motor pin B2, negative
const int pitch_PWM=6;           // PWM, "velocity"

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
int slowSpeed = 100;          // Lower speed

// ##############################################

// Location of switches
int azimuth_min=5;         // Azimuth left switch
int azimuth_max=355;       // Azimuth right switch
int elevation_min=5;       // Elevation lower switch
int elevation_max=85;      // Elevation upper switch

// Which direction are we driving
int motor_direction=0; // 1=forward elevation, 2=backward elevation, 3=forward azimuth, 4=backwward azimuth  

// ##############################################

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);             // opens serial port, sets data rate to 9600 bps
   mySerial.begin(9600);           // second comport
   
   pinMode(sensor_el, INPUT);      // Set switch elevation as an input
   pinMode(sensor_az, INPUT);      // Set switch azimuth as an input

  // IMU function setup
  IMU_setup();  

  // Calibrate the IMU with the switches
  Calibration();
}

void loop() {

    // Update the satelite angles from WX-track and make an convertion 
    UpdateSateliteAngles();

    // Run the motor protocol
    move_motor_protocol();
}
   
