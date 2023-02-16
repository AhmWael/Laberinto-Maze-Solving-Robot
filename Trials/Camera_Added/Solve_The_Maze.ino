void Solve() {
  read_all_TOFs();
  read_Cameras();
  /* for testing TOF
//  Serial.print("TOF_C:");
//  Serial.print(TOF_C);
//  Serial.print("\tTOF_R:");
//  Serial.println(TOF_R);
*/

  if(!isBlue())
  {
    blue_flag = 0;
    blue_counter = 0;
  }
  else
    blue_counter++;
  if ((isBlue()) && !(blue_flag) && blue_counter >= 400) {
    timer = millis();
    while (millis() - timer <= 5000) { // wait half a second
      read_all_TOFs();
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    blue_flag = 1;
    blue_counter = 0;
  }
  else
  {
    if (TOF_R > 200) { // if there isn't a wall to your right, turn right then move forward for one tile
      Move('R');
      Move('F');
    }
    else if (TOF_C < 100) { // if there is a wall in front of you, turn left
      Move('L');
    }
    else { // if the there is a wall to your right and there is no wall in front of you, move forward
      Move('F');
    }
  }
}
