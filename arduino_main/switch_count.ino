void switch_count(){
/*
 * This function is keeping track of how many turns (in roll) the parabola have made
 * When the parabola have turned one way too much it rotates back to initial position
 * 
 * Date_ 2018-07-03
 * 
 */
    // Add or remove 1 from switch_count_az depending on driving direction
    if (motor_direction_2==1){                                   // If a switch is passed positive (CW)
      switch_count_az++;                                         // Add 1 to switch count
      }
    if(motor_direction_2==2){                                    // If a switch is passed negative (CCW) 
      switch_count_az--;                                         // Subtrack 1 from switch count  
      }

    Serial.print(F("Azimutal switch activated, switch count has now the value: "));
    Serial.println(switch_count_az);

    // ######################################################################
    // IF WE HAVE TURNED TOO MUCH, DRIVE AROUND AGAIN  

    // If we have turned too much in positive direction
    if (switch_count_az>= 1){     

        Serial.println(F("The parabola have turned too much in positive roll (CW), it's now rotating back")); 
        Serial.println(F("Waiting to switch to be activated to achive zero position.."));

        Roll_Brake();                                                // Brake
        Pitch_Brake();                                               // Brake
      
        // Run negative until switch is activated, i.e. run until hitting switch. Calibrate roll to that angle and then run positive until unactivated. 
        // Run negative until hitting switch
        while(digitalRead(sensor_az)==LOW){                               
          Roll_Negative(fastSpeed);
          delay(100);                                       // Normal delay 
        }
        Roll_Brake();                                       // Brake
        rolldeg=0;                                          // Calibrate rolldeg

        // Run positive until switch unactivated
        while(digitalRead(sensor_az)==HIGH){                               
          Roll_Positive(fastSpeed);
          delay(100);                                       // Normal delay 
        }
        Roll_Brake();                                       // Brake
        switch_count_az = 0;                                // Reset switch_count_az
        Serial.println(F("Zero position achived, continuing program"));
        return;
      }
      
    // If we have turned too much in negative direction
    if (switch_count_az<= -2){ 
        Serial.println(F("The parabola have turned too much in negative roll (CCW), it's now rotating back"));
        Serial.println(F("Waiting for switch to pass to achive zero position.."));

        Roll_Brake();                                                // Brake
        Pitch_Brake();                                        // Brake
      
        // Run positive until switch is actiated and then unactivated, i.e. run past switch. Then alibrate roll to that angle. 
        while(digitalRead(sensor_az)==LOW){                               
          Roll_Positive(fastSpeed);
          delay(100);                                       // Normal delay 
        }
        while(digitalRead(sensor_az)==HIGH){                               
          Roll_Positive(fastSpeed);
          delay(100);                                       // Normal delay 
        }
        Roll_Brake();                                       // Brake
        rolldeg=0;                                          // Update rolldeg 
        switch_count_az = 0;                                // Reset switch_count_az

        Serial.println(F("zero position achived, continuing program"));
        return;
      }

   Serial.print(F("Updateing roll degree with +- 360.."));
   Serial.print("old roll deg: ");
   Serial.println(rolldeg);

   if ((motor_direction_2==1) && (switch_count_az > -2)){ 
      rolldeg = rolldeg - 360; 
   }
   
   if ((motor_direction_2==2) && (switch_count_az < 1)){   
    if (rolldeg > 0){                              
      rolldeg = 360 - rolldeg;
    } else {
      rolldeg = 360 + rolldeg;
    }
   }

   Serial.print("New roll deg: ");
   Serial.println(rolldeg);
  
}
