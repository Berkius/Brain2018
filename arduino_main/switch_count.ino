//A function to keep track of how many turns the parabola have made in certain directions
void switch_count(){
    
    if ((motor_direction==3)&&(switch_count<=0)){           //If a switch is passed clockwise and its the first time it passes the switch clockwise  
      switch_count_az++;                                    //Add 1 to switch count
      }
    if((motor_direction==4)&&(switch_count>=0)){            //If a switch is passed counter clockwise and its the first time it passes the switch counter clockwise    
      switch_count_az--;                                    //Subtrack 1 from switch count  
      }
    if ((motor_direction==3) && (switch_count_az>0)&& (abs(rolldeg)>=180)){      //clockwise direction hit of the switches, switch has been passed in one direction ones earlier and rolldeg is 180 degrees  
        Roll_Brake();                                       //Brake
        while(switch_count_az!=0){                          //Turn backwards until switch_count is resotred and the antenna is at zero again
          Roll_Negative();                                  //
          }
        Roll_Brake();                                       //Brake
        rolldeg=0;                                          //Update rolldeg 
      }
    if ((motor_direction==4)&&((switch_count_az)<=-1)&&(abs(rolldeg)>=180)){  //clockwise direction hit of the switches, switch has been passed in one direction ones earlier and rolldeg is 180 degrees
        Roll_Brake();                                       //Brake
        while(switch_count_az!=0){                          //Turn forwwards until switch_count is resotred and the antenna is at zero again
          Roll_Positive();                                  //
          }
        Roll_Brake();                                       //Brake
        rolldeg=0;                                          //Update rolldeg 
      }
  
}
