void UpdateSateliteAngles(){
/*
 * Updates the coordiante angles for the satelite 
 * 
 * Calling the function serialEvent and updates the string receivedChars, this is then computed in Extract_Datas where the satelite angles are achived
 * The function check if a satelite coordintaes has been updates for the last 5s, if not we don't keep tracking
 * The function also sets the value of the satelite elevation to our minimum value if it's too low
 * 
 * Date: 2018-07-08
 * 
 */


// How long between we check if there hasn'nt been a satelite
const unsigned long periodTrack = 5000; 


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

    // If satelite coords is obtained set satelite_is_available to high and start tracking (tracking == HIGH)
    if (coordinates_obtained > 0){
      satelite_is_available = HIGH;
      tracking == HIGH; 
    }

      // See if the there hase'nt been any updates of the coords for the last 5s
      currentMillisTrack = millis();                                             // Get the current "time"
      if (currentMillisTrack - startMillisTrack >= periodTrack){                 // Test whether the period has elapsed, if true update satelite angles 
         if (satelite_is_available == LOW){
          tracking = LOW;                                                        // Turn off the tracking
         }
         satelite_is_available = LOW;
         startMillisTrack = millis();           // Reset start time
      }

     //Serial.println("Ending UpdateSateliteAngles");

     // If the elevation of the satelite is lower than the lowest the parabola can go, set the degree to the lowest 
     if (EL_degree < (elevation_min + safe_marg)){
      EL_degree = (elevation_min + safe_marg);
     }
  
}
