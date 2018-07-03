void End_switches(){
/*
 This Function is to use the Brake when hiting the endswitches 
 Looks at which switch was activated and which direction we we ran latest. Then update offset to motor angle
 */
 //Serial.println(F("Entering End_switches"));

 int safe_marg=1;

  // Brake motors
  Pitch_Brake(); 
  Roll_Brake();
  delay(1000);

  Serial.println("Calibrating new angles..");

  // Get pitch angle (cant get roll..)               
  getCurrentPitch();
  
  if (motor_direction_1==1){                                                  //when going in Pitch positive
      offset_el=elevation_max-pitchdeg;                                     //Calibrate the offset after hitting the switch 
        getCurrentPitch();
        while((elevation_max - pitchdeg) < safe_marg){                      //As long as the angle is out of the interval keep on going
          Pitch_Negative(fastSpeed);                                        //Back up from the switch, As long as the angle is out of the interval keep on going
          delay(50);
          getCurrentPitch(); 
          }
          Pitch_Brake();
      }
  if (motor_direction_1==2){                                                  //when going in Pitch negative
        offset_el=elevation_min-pitchdeg;                                   //Calibrate the offset after hitting the switch 
        getCurrentPitch();  
        while((pitchdeg-elevation_min) < safe_marg){                      //As long as the angle is out of the interval keep on going
          Pitch_Positive(fastSpeed);                                        //Back up from the swtich, As long as the angle is out of the interval keep on going
          delay(50);
          getCurrentPitch();  
          }
          Pitch_Brake();
      } 
// Azimuth switches are controlled in switch_count
  /*    
  if (motor_direction_2==1){
        rolldeg = azimuth_max;
  
        while((azimuth_max - rolldeg) < safe_marg){                          //As long as the angle is out of the interval keep on going
          Roll_Negative(fastSpeed);                                         //Back up from the swtich, As long as the angle is out of the interval keep on going
          delay(50);
          getCurrentRoll(50); 
        }  
        Roll_Brake();
      }
  if (motor_direction_2==2){
        rolldeg = azimuth_max;
  
        while((rolldeg-azimuth_min) < safe_marg){                          //As long as the angle is out of the interval keep on going
          Roll_Positive(fastSpeed);                                         //Back up from the swtich, As long as the angle is out of the interval keep on going
          delay(50);
          getCurrentRoll(50); 
        }  
        Roll_Brake();
     }
   //Serial.println(F("Ending End_switches"));

   Serial.println("Calibrating done");
*/
}
