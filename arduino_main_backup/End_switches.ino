void End_switches(){
  Roll_Brake();
  Pitch_Brake();
  getCurrentAngles();
  if (motor_direction==1){
        offset_el=abs(elevation_min-pitchdeg);
        while((pitchdeg-offset_el)!=(elevation_min+safe_marg)){         //As long as the angle is out of the interval keep on going
          Pitch_Negativ(setupSpeed);
          getCurrentAngles();
          delay(1000);          //Ta bort ev.
        }
  if (motor_direction==2){
        offset_el=abs(elevation_max-pitchdeg);
        getCurrentAngles();
        while((pitchdeg-offset_el)!=(elevation_max-safe_marg)){         //As long as the angle is out of the interval keep on going
          Pitch_Positiv(setupSpeed);
          getCurrentAngles();
          delay(1000);
        } 
  if (motor_direction==3){
        //offset_az=abs(azimuth_min-rolldeg); Vad har vi för feedback i Azimuth 
        
        }  
  if (motor_direction==2){
        //offset_az=abs(azimuth_max-rolldeg); Vad har vi för feedback i Azimuth
        
        }                   
  }
