//A function to keep track of how many turns the parabola have made in certain directions
void switch_count(){
    
    if ((motor_direction_2==1)&&(switch_count_az<=0)){           //If a switch is passed clockwise and its the first time it passes the switch clockwise  
      switch_count_az++;                                    //Add 1 to switch count
      }
    if((motor_direction_2==2)&&(switch_count_az>=0)){            //If a switch is passed counter clockwise and its the first time it passes the switch counter clockwise    
      switch_count_az--;                                    //Subtrack 1 from switch count  
      }
    if ((motor_direction_2==1) && (switch_count_az>1)){      //clockwise direction hit of the switches, switch has been passed in one direction ones earlier and rolldeg is 180 degrees  
        Roll_Brake();                                       //Brake
        while(switch_count_az!=0){                          //Turn backwards until switch_count is resotred and the antenna is at zero again
          Roll_Negative(fastSpeed);
          if ((motor_direction_2==2)&&(digitalRead(sensor_az)==HIGH)&&(switch_count_az>1)){
            Serial.print("Going backwards, switch count should be 2");
            Serial.println(switch_count_az);
          }
         /*
          if ((motor_direction_2==2)&&(digitalRead(sensor_az)==HIGH)&&(switch_count_az==1)){
            Serial.print("switch count is 1");
            Serial.println(switch_count);
          }
          if ((motor_direction_2==2)&&(digitalRead(sensor_az)==HIGH)&&(switch_count_az==1)){
            Serial.print("switch count is 0");
            Serial.println(switch_count);
          }
          
          */
        }
        Roll_Brake();                                       //Brake
        rolldeg=0;                                          //Update rolldeg 
      }
    if ((motor_direction_2==2)&&((switch_count_az)<-1)){  //clockwise direction hit of the switches, switch has been passed in one direction ones earlier and rolldeg is 180 degrees
        Roll_Brake();                                       //Brake
        while(switch_count_az!=0){                          //Turn forwwards until switch_count is resotred and the antenna is at zero again
          Roll_Positive(slowSpeed);                          
          
          }
        Roll_Brake();                                       //Brake
        rolldeg=0;                                          //Update rolldeg 
      }
  Serial.print("Switchcount for az: ");
  Serial.println(switch_count_az);
  
}
