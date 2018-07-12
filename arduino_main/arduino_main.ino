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
const int sensor_el = A3;         // Switch for elevtion
const int sensor_az = A2;         // Switch for azimuth

// Motor 1
const int roll_IN1=4;            // Motor pin A1, positive
const int roll_IN2=9;            // Motor pin B1, positive
const int roll_PWM=6;            // PWM, "velocity"

// Motor 2
const int pitch_IN1=7;           // Motor pin A2, positive
const int pitch_IN2=8;           // Motor pin B2, negative
const int pitch_PWM=5;           // PWM, "velocity"

// Define the string PITCH as 0 and ROLL as 1
#define PITCH 0
#define ROLL  1
// ##############################################
// IMU 
// define variables for acceleromter
ADXL345 acc;                               // variable adxl is an instance of the ADXL345 libary

int ax,ay,az;                              // Reserved storage slots for the accelerometer libary 
float aoffsetX, aoffsetY, aoffsetZ;        // ??

// Define variables to gyroscope
ITG3200 gyro = ITG3200();
float gx, gy, gz;                          // Reserved storage slots for the gyroscope libary 

// other IMU related
float rolldeg, pitchdeg;                   // The angle of the motors [degree]
float delta_roll, delta_pitch;             // The offset between the aceelerometer value and the actual value (from switch) [degree]

float offset_el=0;                         // The elevation offset measured from the elevation switch


// #############################################
// SWITCH VARIBALES

int switch_count_az=0;                     // Count number of laps the parabola have turned in a specific direction 

int switch_pre_value = 0;                  // The previously value of the azimuth switch (to not get it to log multiple hits in one activation)
int switch_value_counter_az = 0;           // Counter for nr of time az/roll switchen has been hitted in a row
int switch_value_counter_az_low = 0;       // Counter for nr of time az/roll switchen has NOT been hitted in a row
int switch_value_counter_el = 0;           // Counter for nr of time el/pitch switchen has been hitted in a row
int switch_value_counter_el_low = 0;       // Counter for nr of time el/pitch switchen has NOT been hitted in a row

// Location of switches
int elevation_min=20;                      // Elevation lower switch
int elevation_max=92;                      // Elevation upper switch

int counter_max = 4;                                                    // how many times we need to have a high or low in a row

// ##############################################
// MOTOR SPEED
int fastSpeed = 200;                       // High speed, used the first time adjusting to new satelite and when going back to initial pos
int slowSpeed = 130;                       // Low speed, used while tracking 

// ##############################################
// OTHER

// Which direction are we driving
int motor_direction_1=0;                   // 1=forward elevation, 2=backward elevation 
int motor_direction_2=0;                   // 1=forward azimuth, 2=backwward azimuth

int safe_marg = 8;                         // How close to the switch we allow the parabola to go
int calibration_done = 0;                  // If the calibration is compleated, so safe margin is ingored during calibration (implemented in Drive_and_Brake)

// See if a satelite is avaliable(/if we are tracking)
int tracking = LOW;                        // If we are tracking right now
int coordinates_obtained;                  // If we obtained coordinates from WX-track
int satelite_is_available = LOW;           // If we have obtained coordinateds in the last 10s

int fast_adjustment = 1;                   // First time it tries to adjust to a new satlite we want to drive fast

// Time keeping track on how often we should update satalite angles
unsigned long startMillisTrack;             // Starting time
unsigned long currentMillisTrack;           // Current time

// How long time we are driving

unsigned long DrivingTimeStart;             // Starting time

unsigned long DrivingTimeStartBrake = 0;                        // Starting time motors

float angular_velocity_roll;                // Velocity of the azimuth motor, from gyro

// ##############################################

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);                     // opens serial port, sets data rate to 9600 bps
   mySerial.begin(9600);                   // second comport
   
   pinMode(sensor_el, INPUT_PULLUP);       // Set switch elevation as an input
   pinMode(sensor_az, INPUT_PULLUP);       // Set switch azimuth as an input

   Serial.println(F("STARTING SETUP OF IMU AND CALIBRATION OF ANGLES"));

  // Calibrate the IMU with the switches
  Calibration();

  Serial.println(F("\n SETUP AND CALIBRATION DONE. STARTING MAIN LOOP"));

  startMillisTrack = millis();              // Initial start time for how often we update satelite angles
}

void loop() {

    Serial.println(F("\n NEW LOOP (MAIN): "));

    // Update the satelite angles from WX-track and make an convertion 
    UpdateSateliteAngles();


  if (tracking == LOW){
        
        // Reset counters
        reset_counters();
        
        Serial.println("No satellite is available, going back to initial position");
        //initial_pos();
        fast_adjustment = 1;
      } else {

        // Reset counters
        reset_counters();
        
        Serial.print(F("Motor roll/AZ angle: "));   
        Serial.println(rolldeg); 
    
        Serial.print("Satelite roll/AZ angle: ");
        Serial.println(AZ_degree);
    
        Serial.print(F("Motor pitch/EL angle: "));   
        Serial.println(pitchdeg); 
    
        Serial.print("Satelite pitch/EL angle: ");
        Serial.println(EL_degree);
    
        // Run the motor protocol
        move_motor_protocol();

        
     } 
}
   
