/*
 * Drives the motors 
 * 
 * 
 */


#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

short usSpeed = 150;  //default motor speed
unsigned short usMotor_Status = BRAKE;
int switch_value_counter_el = 0;

int drivingEL = 0;
int drivingAZ = 0;

// Microswitches 
const int sensor_el = A2;         // Switch for elevtion
 
void setup()                         
{
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  //pinMode(CURRENT_SEN_1, OUTPUT);
  //pinMode(CURRENT_SEN_2, OUTPUT);  

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

  pinMode(sensor_el, INPUT_PULLUP);       // Set switch elevation as an input

  Serial.begin(9600);              // Initiates the serial to do the monitoring 
  Serial.println("Begin motor control");
  Serial.println(); //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. STOP");
  Serial.println("w. POSITIVE/CW ELEVATION");
  Serial.println("s. NEGATIVE/CCW ELEVATION");
  Serial.println("a. POSITIVE/CW AZIMUTH");
  Serial.println("d. NEGATIVE/CCW AZIMUTH");
  //Serial.println("4. READ CURRENT");
  Serial.println("2. RUN ELEVATION NEGATIVE/CCW TO SWITCH");
  Serial.println("+. INCREASE SPEED");
  Serial.println("-. DECREASE SPEED");
  Serial.println();

}

void loop() 
{
  char user_input;   

  
  
  while(Serial.available())
  {
    user_input = Serial.read(); //Read user input and trigger appropriate function
    digitalWrite(EN_PIN_1, HIGH);
    digitalWrite(EN_PIN_2, HIGH); 
     
    if (user_input =='1')
    {
       Stop();
    }
    else if(user_input =='w')
    {
      ForwardEL();
    }
    else if(user_input =='d')
    {
      ForwardAZ();
    }
    else if(user_input =='s')
    {
      ReverseEL();
    }
        else if(user_input =='a')
    {
      ReverseAZ();
    }
        else if(user_input =='2')
    {
      RunToSwitch();
    }
    else if(user_input =='+')
    {
      IncreaseSpeed();
    }
    else if(user_input =='-')
    {
      DecreaseSpeed();
    }
    else
    {
      Serial.println("Invalid option entered.");
    }
      
  }
}

void Stop()
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status, 0);
  drivingEL = 0;
  drivingAZ = 0;
}

void ForwardEL()
{
  Serial.println("Positive/CW elevation motor");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  drivingEL = 1;
}

void ForwardAZ()
{
  Serial.println("Positive/CW azimuth motor");
  usMotor_Status = CW;
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  drivingAZ = 1;
}

void ReverseEL()
{
  Serial.println("Negative/CCW elevation motor");
  usMotor_Status = CCW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  drivingEL = 1;
}
void ReverseAZ()
{
  Serial.println("Negative/CCW azimuth motor");
  usMotor_Status = CCW;
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  drivingAZ = 1;
}

void IncreaseSpeed()
{
  usSpeed = usSpeed + 10;
  if(usSpeed > 255)
  {
    usSpeed = 255;  
  }
  
  Serial.print("Speed +: ");
  Serial.println(usSpeed);

  if (drivingAZ == 1){
    motorGo(MOTOR_2, usMotor_Status, usSpeed); 
    }

   if (drivingEL == 1){
    motorGo(MOTOR_1, usMotor_Status, usSpeed); 
    }
   
}

void DecreaseSpeed()
{
  usSpeed = usSpeed - 10;
  if(usSpeed < 0)
  {
    usSpeed = 0;  
  }
  
  Serial.print("Speed -: ");
  Serial.println(usSpeed);

  if (drivingAZ == 1){
    motorGo(MOTOR_2, usMotor_Status, usSpeed); 
    }

   if (drivingEL == 1){
    motorGo(MOTOR_1, usMotor_Status, usSpeed); 
    }
}

void RunToSwitch()
{
  Serial.println("SETUP: Running motor negative (CCW) until hitting azimuth switch.");
  Serial.println("You can increase(+)/decrease(-) and stop(1) during setup.");
    Stop();

    while (switch_value_counter_el < 4){                             // When the pitch switch is low 
    // Drive negative direction
    usMotor_Status = CCW;
    motorGo(MOTOR_2, usMotor_Status, usSpeed);                         
    counter_el();

    char user_input; 

    // If we want to go faster or stop
    while(Serial.available())
    {
      user_input = Serial.read(); //Read user input and trigger appropriate function
       if (user_input =='+')
      {
         IncreaseSpeed();
      }
       else if(user_input =='-')
      {
         DecreaseSpeed();
      }
       else if(user_input =='1')
      {
         Stop();
         return;
      }
       else
      {
         Serial.println("Invalid option entered. You can only increase/decrease speed and stop during setup");
      }
      
    }  
   }
  Stop();
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW); 
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_1, pwm); 
  }
  else if(motor == MOTOR_2)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_2, pwm);
  }
}



