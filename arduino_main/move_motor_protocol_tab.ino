  void move_motor_protocol(){
/* Runs the motor(s) a few time units, then check the delta angle (between satetlite position and our position), 
 *  repeat until the delta angle is less than the tolerance
 * 
 * It's possible to drive both motor at the same time to most efficieltly get to the right position
 * Date: 2018-06-15
 */
 
  //Serial.println("Entering move_motor_protocol");

  // Time keeping track on how often we should update satalite angles
  unsigned long startMillis;                                              // Starting time
  unsigned long currentMillis;                                            // Current time
  const unsigned long period = 1000;                                      // How often we should update [ms]
  startMillis = millis();                                                 // Initial start time
  
  int tol = 2;                                                            // Tolerance: How big is delta_roll/delta_pitch allowed to be [degree]
  int time_drive = 15;                                                    // How long to run the motors before updating angles      

  int from_both_to_roll = 0;

  // The speed we want to run the motor on, (depending if its the first time we run this code or not)
  int Speed;                                                     
  if (fast_adjustment == 1){
    Speed = fastSpeed;}
  else{
    Speed = slowSpeed;
  }
     
  // Calculate new delta pitch angle
  delta_pitch = EL_degree-pitchdeg;

  // Calculate new delta roll angle
  delta_roll = AZ_degree-rolldeg;

  
  // Drive as long as any of the delta angles are outside the tolerance
  while(((abs(delta_pitch) > tol) || (abs(delta_roll) > tol)) && (tracking == HIGH)){

    from_both_to_roll = 1;                                    // in both motors

    DrivingTimeStart = millis();                              // Starting time motors
    // If both delta angles are outside tolerance, run both
    while((abs(delta_pitch) > tol) && (abs(delta_roll) > tol) && (tracking == HIGH)){
      if (abs(delta_roll) > 5){
        Speed = fastSpeed;
      }
      // See which direction is the shortest, and start driving that way
      drive_direction(delta_pitch, PITCH, Speed);
      drive_direction(delta_roll, ROLL, Speed);

      
      // Drive the motors "time_drive" ms  before updating angles
      delay_s(time_drive);
  
      // Update pitch angle [degree]
      getCurrentPitch(); // MAYBE ADD IF IMU AVALIABLE THING
  
      // Update angles motor, roll [degree]
      getCurrentRoll();
  
      // Calculate new delta pitch angle
      delta_pitch = EL_degree-pitchdeg;
  
      // Calculate new delta roll angle
      delta_roll = AZ_degree-rolldeg;

      // See if the satalite angles should be updated
      currentMillis = millis();                                   // Get the current "time"
      if (currentMillis - startMillis >= period){                 // Test whether the period has elapsed, if true update satelite angles 
        Serial.println(F("\n DRIVING PITCH AND ROLL MOTOR"));
        UpdateSateliteAngles();                                   // Update satelite angles
        startMillis = millis();                                   // Reset start time

        Serial.print(F("Motor roll/AZ angle: "));   
        Serial.println(rolldeg); 

        Serial.print("Satelite roll/az angle: ");
        Serial.println(AZ_degree);

        Serial.print(F("Motor pitch/EL angle: "));   
        Serial.println(pitchdeg); 

        Serial.print("Satelite pitch/el angle: ");
        Serial.println(EL_degree);

       /*         Serial.print("The switch count: ");
        Serial.println(switch_count_az);

        Serial.print("The direction is ( pos==1, neg==2): ");
        Serial.println(motor_direction_1);*/
      }
    }

    DrivingTimeStart = millis();                              // Starting time motors
    // If only the delta angle for pitch is outside tolerance, run pitch motor
    while((abs(delta_pitch) > tol) && (abs(delta_roll) <= tol) && (tracking == HIGH)){

      from_both_to_roll = 0;                                    // NOT in both motors
      // Brake the roll motor
      Roll_Brake();

      if (DrivingTimeStartBrake != 0){
         float change_in_roll = (millis() - DrivingTimeStartBrake)*0.001 * angular_velocity_roll * 0.4;
         // Just do a piece of this part, so we don't underdoo the azimuth rotation when small increments 
         // no compensation here and no compensation in angularvelocity will make it precise on small increments (but bad at large incrememnts)
         rolldeg = rolldeg + change_in_roll;
         DrivingTimeStartBrake = 0;
      }
  

      // See which direction is the shortest, and start driving that way
      drive_direction(delta_pitch, PITCH, Speed);
      
      // Drive the motor "time_drive" ms  before updating angles
      delay_s(time_drive);
  
      // Update pitch angle [degree]
      getCurrentPitch();

      // Calculate new delta pitch angle
      delta_pitch = EL_degree-pitchdeg;  

      // See if the satalite angles should be updated
      currentMillis = millis();                                   // Get the current "time"
      if (currentMillis - startMillis >= period){                 // Test whether the period has elapsed, if true update satelite angles 
        Serial.println(F("\n DRIVING PITCH MOTOR"));
        UpdateSateliteAngles();                                   // Update satelite angles
        startMillis = millis();                                   // Reset start time

        Serial.print(F("Motor roll/AZ angle: "));   
        Serial.println(rolldeg); 

        Serial.print("Satelite roll/az angle: ");
        Serial.println(AZ_degree);

        Serial.print(F("Motor pitch/EL angle: "));   
        Serial.println(pitchdeg); 

        Serial.print("Satelite pitch/el angle: ");
        Serial.println(EL_degree);

        /*Serial.print("The switch count: ");
        Serial.println(switch_count_az);

        //Serial.print("The direction is ( pos==1, neg==2): ");
        //Serial.println(motor_direction_1);*/
      }
    }
    
    DrivingTimeStart = millis();                              // Starting time motors
    // If only the delta angle for roll is outside tolerance, run roll motor
    while((abs(delta_roll) > tol) && (abs(delta_pitch) <= tol) && (tracking == HIGH)){
      // Brake the pitch motor
      Pitch_Brake();
      if (abs(delta_roll) > 5){
        Speed = fastSpeed;
      }
      if ((DrivingTimeStartBrake != 0) && (from_both_to_roll == 1)){
         float change_in_roll = (millis() - DrivingTimeStartBrake)*0.001 * angular_velocity_roll * 0.4;
         rolldeg = rolldeg + change_in_roll;
         DrivingTimeStartBrake = 0;
         from_both_to_roll = 0;
      }

      // See which direction is the shortest, and start driving that way
      drive_direction(delta_roll, ROLL, Speed);
  
      // Drive the motor "time_drive" ms  before updating angles
      delay_s(time_drive);
  
      // Update roll angle [degree]
      getCurrentRoll();
  
      // Calculate new delta roll angle
      delta_roll = AZ_degree- rolldeg;       

      // See if the satalite angles should be updated
      currentMillis = millis();                                   // Get the current "time"
      if (currentMillis - startMillis >= period){                 // Test whether the period has elapsed, if true update satelite angles 
        Serial.println(F("\n DRIVING ROLL MOTOR"));
        UpdateSateliteAngles();                                   // Update satelite angles
        startMillis = millis();                                   // Reset start time

        Serial.print(F("Motor roll/AZ angle: "));   
        Serial.println(rolldeg); 

        Serial.print("Satelite roll/az angle: ");
        Serial.println(AZ_degree);

        Serial.print(F("Motor pitch/EL angle: "));   
        Serial.println(pitchdeg); 

        Serial.print("Satelite pitch/el angle: ");
        Serial.println(EL_degree);

        /*Serial.print("The switch count: ");
        Serial.println(switch_count_az);

        Serial.print("The direction is ( pos (CW)==1, neg(CCW)==2): ");
        Serial.println(motor_direction_1);*/
      }
    }
  }

  if ((abs(delta_pitch) <= tol) || (abs(delta_roll) <= tol)){
    Roll_Brake();
      if (DrivingTimeStartBrake != 0){
       float change_in_roll = (millis() - DrivingTimeStartBrake)*0.001 * angular_velocity_roll * 0.4;
       rolldeg = rolldeg + change_in_roll;
       DrivingTimeStartBrake = 0;
    }
    Pitch_Brake();
    }

  // Reset counter for nr of time az/roll switchen has been hitted in a row
  if (abs(delta_roll) <= tol){
  switch_value_counter_az = 0;
  }
  //Serial.println("Ending move_motor_protocol");

  // Next tie we run we want to have slow speed
  fast_adjustment = 0;
}

