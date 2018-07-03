void UpdateSateliteAngles(){
  Serial.println("Entering UpdateSateliteAngles");

  serialEvent();                // Goes into the serial event function and saves the data in an array 
  
  // if everything is working and we get the right data and the right data length it will extract the AZIMUTH and ELEVATION 
    if (stringComplete == true  && errorVariable == false) {

      // Remake received satelite coordinates to elevation angle
      Extract_Datas();
      stringComplete = false;
    }
  // if something is wrong with the data length it will not go to the extract datas function and instead go here  
    else if (stringComplete == true && errorVariable == true) {
      stringComplete = false;
      errorVariable = false;
     }
     Serial.print("Az degree: ");
     Serial.println(AZ_degree);

     Serial.print("El degree: ");
     Serial.println(EL_degree);


     Serial.println("Ending UpdateSateliteAngles");
  
}
