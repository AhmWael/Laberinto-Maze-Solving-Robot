void Solve() {
  read_all_TOFs();
  read_Cameras();
  if(isBlue() == true){
    timer = millis();
    while (millis() - timer <= 5000) {
      read_all_TOFs();
      read_Cameras();
      MoveWheels(LOW, 0, LOW, 0, "Stop");
      
    }
  }
//  Serial.print("TOF_C:");
//  Serial.print(TOF_C);
//  Serial.print("\tTOF_R:");
//  Serial.println(TOF_R);

//  Serial.print("posil: ");
//  Serial.print(posil);
//  Serial.print("\tposir:");
//  Serial.println(posir);

//  MoveWheels(HIGH, 174, HIGH, 200, "Forward");
  
  if (TOF_R > 200) {
    Move('R');
    Move('F');
  }
  else if (TOF_C < 100) {
    Move('L');
  }
  else {
    Move('F');
  }
}
