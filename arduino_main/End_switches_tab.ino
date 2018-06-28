void End_switches(){
/*
 This Function is to use the Brake when hiting the endswitches 
 Looks at which switch was activated and which direction we we ran latest. Then update offset to motor angle
 */
 Serial.println("Entering End_switches");

// Location of switches
int azimuth_min=0;         // Azimuth left switch
int azimuth_max=0;         // Azimuth right switch
int elevation_min=5;       // Elevation lower switch
int elevation_max=85;      // Elevation upper switch

 int safe_marg=1;

  Pitch_Brake();                
  getCurrentAngles();
  if (motor_direction==1){                                              //when going in Pitch positive
        offset_el=abs(elevation_min-pitchdeg);                          //Calibrate the offset after hitting the switch 
        while((pitchdeg-offset_el)!=(elevation_min+safe_marg)){         //Back up from the swtich, As long as the angle is out of the interval keep on going
          Pitch_Negative(setupSpeed);
          getCurrentAngles(); 
          }
        }
  if (motor_direction==2){                                              //when going in Pitch negative
        offset_el=abs(elevation_max-pitchdeg);                          //Calibrate the offset after hitting the switch 
        while((pitchdeg-offset_el)!=(elevation_max-safe_marg)){         //As long as the angle is out of the interval keep on going
          Pitch_Positive(setupSpeed);                                    //Back up from the swtich, As long as the angle is out of the interval keep on going
          getCurrentAngles();  
          }
        } 
  if (motor_direction==3){
        //offset_az=abs(azimuth_min-rolldeg); Vad har vi för feedback i Azimuth 
        }  
  if (motor_direction==2){
        //offset_az=abs(azimuth_max-rolldeg); Vad har vi för feedback i Azimuth
        }
   Serial.println("Ending End_switches");
}
