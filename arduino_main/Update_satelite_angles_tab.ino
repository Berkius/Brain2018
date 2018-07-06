void UpdateSateliteAngles(){

  
const unsigned long periodTrack = 3000; 
int isavailable;

  //Serial.println("Entering UpdateSateliteAngles");

  serialEvent();   // Goes into the serial event function and saves the data in an array 
  
  // if everything is working and we get the right data and the right data length it will extract the AZIMUTH and ELEVATION 
    if (stringComplete == true  && errorVariable == false) {
      //Serial.println("error false");  
      // Remake received satelite coordinates to elevation angle
      Extract_Datas();
      stringComplete = false;
    }
  // if something is wrong with the data length it will not go to the extract datas function and instead go here  
    else if (stringComplete == true && errorVariable == true) {
      stringComplete = false;
      errorVariable = false;
     }


    if (tracky > 0){
      isavailable = HIGH;
    }

      // See if the satalite angles should be updated
      currentMillisTrack = millis();                                   // Get the current "time"
      if (currentMillisTrack - startMillisTrack >= periodTrack){                 // Test whether the period has elapsed, if true update satelite angles 
         if (isavailable == HIGH){
          tracking = HIGH;
         }
         isavailable = LOW;
         startMillisTrack = millis();           // Reset start time
      }

     //Serial.println("Ending UpdateSateliteAngles");

     if (EL_degree < (elevation_min + safe_marg)){
      EL_degree = (elevation_min + safe_marg);
     }
  
}
