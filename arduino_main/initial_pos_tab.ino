void initial_pos(){
/*
 * Drives the parabola back to initial position
 * 
 * Date: 2018-07-08
 */

// Init pos
 int roll = 10;
 int pitch = 40;

 int Droll = roll-rolldeg;
 int Dpitch = pitch-pitchdeg;
 

 DrivingTimeStart = millis();                              // Starting time motors

// Rotate past switch if needed
while (switch_count_az == -1){
  Roll_Positive(fastSpeed);
  delay_s(100);
  getCurrentRoll();
  }

// Drive roll motor to right pos
while (abs(Droll) < 5){
  if (Droll > 0){
    Roll_Positive(fastSpeed);
    }
  else {
    Roll_Negative(fastSpeed);
    }
  delay_s(100);
  getCurrentRoll();
  Droll = roll-rolldeg;
  }

// Drive pitch motor to right pos
while (abs(Dpitch) < 5){
  if (Dpitch > 0){
    Pitch_Positive(fastSpeed);
    }
  else {
    Pitch_Negative(fastSpeed);
    }
  delay_s(100);
  getCurrentPitch();
  Dpitch = pitch-pitchdeg;
  }
}
