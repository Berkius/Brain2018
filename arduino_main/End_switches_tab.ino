void End_switches(){
/* This code is runned when the elevation switch is hitted
 * 
 * Looks at which switch was activated and which direction we drove the motor latest. 
 * Then update offset to motor angle and drive the motor until switch is unactivated
 * 
 * Date: 2018-07-03
 */
 //Serial.println(F("Entering End_switches"));

 int safe_marg=3;

  // Brake motors
  Pitch_Brake(); 
  Roll_Brake();
  delay(1000);

 
  // Get pitch angle (cant get roll..)               
  getCurrentPitch();

  // When going in Pitch positive
  if (motor_direction_1==1){   
    Serial.println(F("Calibrating new pitch offset(top switch hitted).."));                                             
      offset_el = elevation_max - (pitchdeg - offset_el);                               // Calibrate the offset after hitting the switch 

    // Drive motors until switch is unactivated
    switch_el_value_counter = 10;
    while(switch_el_value_counter >= 3){  
      Pitch_Negative(slowSpeed);                              // Drive negative pitch
      switch_el_value_counter = counter_el();
    }
    
      while(pitchdeg > (elevation_max - safe_marg) ){                
        Pitch_Negative(slowSpeed);                                       
        delay(50);
        getCurrentPitch(); 
        }      
      Pitch_Brake();
    }

  // When going in Pitch negative
  else if (motor_direction_1==2){        
    Serial.println(F("Calibrating new pitch offset(bottom switch hitted).."));                                         
      offset_el = elevation_min - (pitchdeg - offset_el);                               // Calibrate the offset after hitting the switch 

    // Drive motors until switch is unactivated
    switch_el_value_counter = 10;
    while(switch_el_value_counter >= 3){  
      Pitch_Positive(slowSpeed);                              // Drive negative pitch
      switch_el_value_counter = counter_el();
    }

      // Drive motors until switch is unactivated
      while(pitchdeg < (safe_marg + elevation_min)){                        
        Pitch_Positive(fastSpeed);                                
        delay(50);
        getCurrentPitch();  
        }        
      Pitch_Brake();
    } 
Serial.println(F("Calibrating done"));
}
