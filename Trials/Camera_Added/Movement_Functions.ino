/*
  this function is responsible for moving the motors
*/
void MoveWheels (bool dir_l, int speed_l, bool dir_r, int speed_r, String to_print) {
  digitalWrite(l_dir, !(dir_l));
  analogWrite(l_pwm, speed_l);
  digitalWrite(r_dir, !(dir_r));
  analogWrite(r_pwm, speed_r);
  //Serial.println(to_print);
}

void Move(char movement_dir) {
  read_all_TOFs();
  if (movement_dir == 'F') { // if the robot has to move forward according to the right hand rule
    while ((((posir + posil) / 2) <= (tile_length * 1)) && (TOF_C > 85)) { // to move one tile forward
      read_Cameras();
      if (!isBlue())
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
      read_all_TOFs();
      if (isBlack()) {
        //        int temp_posil = posil, temp_posir = posir;
        posil = 0;
        posir = 0;
        while (((posir + posil) / 2) >= -500) {
          MoveWheels(LOW, 200, LOW, 200, "Back");
        }
        Move('R');
        Move('R');
        return ;
      }
      if (TOF_R < 70)
      { // adjust quickly to the left
        int temp_posil = posil;
        int temp_posir = posir;
        while (TOF_R < 78) { // to turn till the reading of the right TOF is 78
          MoveWheels(LOW, 200, HIGH, 200, "Left");//LOW, 200, HIGH, 200, "Left"
          read_all_TOFs();
        }
        posir = temp_posir;
        posil = temp_posil;
      }
      else if ((TOF_R > 85) && (TOF_R <= 105)) // 135 // adjust the robot to turn right slightly
      {
        pwm_L = max(174, 174 + ((TOF_R - 85) / 50.0) * 80.0);
        pwm_R = max(200, 200 - ((TOF_R - 85) / 50.0) * 54.0);
      }
      else if ((TOF_R > 105) && (TOF_R <= 200)) // adjust robot to turn right sharply
      {
        pwm_L = 250;
        pwm_R = 174;
      }
      else { // robot moves in a straight line
        pwm_R = 200;
        pwm_L = 193;
      }
      MoveWheels(HIGH, pwm_L, HIGH, pwm_R, "Forward");
    } // end of while loop
    timer = millis();
    while (millis() - timer <= 500) { // wait half a second
      read_all_TOFs();
      read_Cameras();
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    Serial.println("New Tile Reached");
    tile_length = 2330;
    posir = 0;
    posil = 0;
    left_turn = 0;
  }
  else if (movement_dir == 'R') {
    posil = 0;
    posir = 0;
    while (abs(posir - posil) <= 2750) { // turn 90 degrees to the right
      read_Cameras();
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;
      MoveWheels(HIGH, 200, LOW, 200, "Right");
    }
    timer = millis();
    while (millis() - timer <= 500) { // wait half a second
      read_all_TOFs();
      read_Cameras();
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    tile_length = 2500;
    posir = 0;
    posil = 0;
    left_turn = 0;
  }
  else {
    posir = 0;
    posil = 0;
    while (abs(posir - posil) <= 2750) { // turn 90 degrees to the left
      read_Cameras();
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;
      MoveWheels(LOW, 200, HIGH, 200, "Left");
    }
    timer = millis();
    while (millis() - timer <= 500) { // wait half a second
      read_all_TOFs();
      read_Cameras();
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    tile_length = 2330;
    if (left_turn) {
      tile_length = 1800;
    }
    posir = 0;
    posil = 0;
    left_turn = 1;
  }
}
