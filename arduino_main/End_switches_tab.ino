void End_switches(){
/* This code is runned when the elevation switch is hitted
 * 
 * Looks at which switch was activated and which direction we drove the motor latest. 
 * Then update offset to motor angle and drive the motor until switch is unactivated
 * 
 * Date: 2018-07-03
 */
 //Serial.println(F("Entering End_switches"));

 int safe_marg=1;

  // Brake motors
  Pitch_Brake(); 
  Roll_Brake();
  delay(1000);

  Serial.println(F("Calibrating new pitch offset.."));

  // Get pitch angle (cant get roll..)               
  getCurrentPitch();

  // When going in Pitch positive
  if (motor_direction_1==1){                                                
      offset_el = elevation_max - pitchdeg;                               // Calibrate the offset after hitting the switch 

      // Drive motors until switch is unactivated
      while((elevation_max - pitchdeg) < safe_marg){                
        Pitch_Negative(fastSpeed);                                       
        delay(50);
        getCurrentPitch(); 
        }      
      Pitch_Brake();
    }

  // When going in Pitch negative
  if (motor_direction_1==2){                                                
      offset_el = elevation_min - pitchdeg;                               // Calibrate the offset after hitting the switch  

      // Drive motors until switch is unactivated
      while((pitchdeg-elevation_min) < safe_marg){                        
        Pitch_Positive(fastSpeed);                                
        delay(50);
        getCurrentPitch();  
        }        
      Pitch_Brake();
    } 
Serial.println(F("Calibrating done"));
}
