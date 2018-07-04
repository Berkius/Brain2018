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
char receivedChars[28];             // array of chars to store the values in
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

#define PITCH 0
#define ROLL  1

// ##############################################
// Define varibales to acceleromter
ADXL345 acc;                               //variable adxl is an instance of the ADXL345 libary

int ax,ay,az;                              // Reserved storage slots for the accelerometer libary 

float rolldeg, pitchdeg;                         // The angle of the motors [degree]
float aoffsetX, aoffsetY, aoffsetZ;        // ??
float delta_roll, delta_pitch;             // The offset between the aceelerometer value and the actual value (from switch) [degree]

// Motor offset (from accelerometer)
float offset_el=0;                         // The elevation offset measured from the elevation switch
int switch_count_az=0;                     // Count number of laps the parabola have turned in a specific direction 

// Define varibales to gyroscope
ITG3200 gyro = ITG3200();
float gx, gy, gz;                          // Reserved storage slots for the gyroscope libary 

// ##############################################
// MOTOR SPEED
int fastSpeed = 255;                       // Full speed
int slowSpeed = 100;                       // Lower speed

// ##############################################
// OTHER

// Location of switches
int azimuth_min=5;                         // Azimuth left switch
int azimuth_max=355;                       // Azimuth right switch
int elevation_min=5;                       // Elevation lower switch
int elevation_max=85;                      // Elevation upper switch

// Which direction are we driving
int motor_direction_1=0;                   // 1=forward elevation, 2=backward elevation 
int motor_direction_2=0;                   // 1=forward azimuth, 2=backwward azimuth

int switch_pre_value = 0;                  // The previously value of the azimuth switch (to not get it to log multiple hits in one activation)
int switch_value_counter = 0;              // Counter for nr of time az/roll switchen has been hitted in a row
// ##############################################

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);                     // opens serial port, sets data rate to 9600 bps
   mySerial.begin(9600);                   // second comport
   
   pinMode(sensor_el, INPUT_PULLUP);       // Set switch elevation as an input
   pinMode(sensor_az, INPUT_PULLUP);       // Set switch azimuth as an input

   Serial.println(F("STARTING SETUP OF IMU AND CALIBRATION OF ANGLES"));

  // IMU function setup
  IMU_setup();  

  // Calibrate the IMU with the switches
  Calibration();

  Serial.println(F("\n SETUP AND CALIBRATION DONE. STARTING MAIN LOOP"));

}

void loop() {

    Serial.println(F("\n NEW LOOP (MAIN): "));

    Serial.print(F("Roll angle: "));   
    Serial.println(rolldeg); 

    Serial.print(F("Pitch angle: "));   
    Serial.println(pitchdeg); 

    // Update the satelite angles from WX-track and make an convertion 
    UpdateSateliteAngles();

    // Run the motor protocol
    move_motor_protocol();
}
   
