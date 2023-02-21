void MoveWheels (bool dir_l, short speed_l, bool dir_r, int speed_r, String to_print) {
  // This function is responsible for moving the motors
  digitalWrite(l_dir, !(dir_l));
  analogWrite(l_pwm, speed_l);
  digitalWrite(r_dir, !(dir_r));
  analogWrite(r_pwm, speed_r);
  //Serial.println(to_print);
}

void Move(char movement_dir, short tile_length, short turn_angle) {
  read_all_TOFs();
  if (movement_dir == 'F') { // if the robot has to move forward according to the right hand rule
    while ((((posir + posil) / 2) <= (tile_length * 1)) && (TOF_C > 85)) { // to move one tile forward
      if (tilt && digitalRead(tilt_asc) == 0)
      {
        tilt = 0;
        tile_length += 100;
      }
      else if (digitalRead(tilt_asc) == 1) {
        tilt = 1;
      }
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;

      if (!isBlack())
      {
        black_counter = 0;
      }
      else
        black_counter++;

      if ((isBlue()) && !(blue_flag) && blue_counter >= 4000) {
        timer = millis();
        while (millis() - timer <= 5000) { // wait half a second
          read_all_TOFs();
          MoveWheels(HIGH, 0, HIGH, 0, "Stop");
        }
        blue_flag = 1;
        blue_counter = 0;
      }
      read_all_TOFs();
      if (isBlack() && black_counter >= 50) {
        //        int temp_posil = posil, temp_posir = posir;
        posil = 0;
        posir = 0;
        while (((posir + posil) / 2) >= -1200) {
          MoveWheels(LOW, 200, LOW, 200, "Back");
        }
        //        Move('R');
        //        Move('R');
        Move('L', 0, 2950);
        read_all_TOFs();
        if (TOF_C < 100) {
          Move('L', 0, 2950);
        }
        else {
          //            tile_length = 2500;
          Move('X', 2650, 0);
        }
        black_counter = 0;
        return ;
      }
      //      if (TOF_R > 200) {
      if (digitalRead(ir_obstacle_left) == 0 && TOF_C > 200) {
        int temp_posil = posil;
        int temp_posir = posir;
        while (digitalRead(ir_obstacle_left) == 0) { // to turn till the reading of the right TOF is 78
          MoveWheels(HIGH, 200, LOW, 200, "RIGHT");//LOW, 200, HIGH, 200, "Left"
          read_all_TOFs();
          if (TOF_R < 200 && digitalRead(wall_detector_right) == 0)
          {
            if ((posil + posir) / 2 < 0.5 * tile_length)
              read_Cameras(X_Position, Y_Position);
            else
            {
              if (Direction == 0)
                read_Cameras(X_Position, Y_Position + 1);
              else if (Direction == 1)
                read_Cameras(X_Position + 1, Y_Position);
              else if (Direction == 2)
                read_Cameras(X_Position, Y_Position - 1);
              else
                read_Cameras(X_Position - 1, Y_Position);
            }
          }
          //read_Cameras();
        }
        posir = temp_posir;
        posil = temp_posil;
        continue;
      }
      //      if (digitalRead(ir_obstacle_right) == 0 && TOF_C > 200) {
      //        int temp_posil = posil;
      //        int temp_posir = posir;
      //        while (digitalRead(ir_obstacle_right) == 0&& TOF_C > 200) { // to turn till the reading of the right TOF is 78
      //          MoveWheels(LOW, 200, HIGH, 200, "LEFT");//LOW, 200, HIGH, 200, "Left"
      //          read_all_TOFs();
      //          if (TOF_R < 200 && digitalRead(wall_detector_right) == 0)
      //            read_Cameras();
      //          //read_Cameras();
      //        }
      //        posir = temp_posir;
      //        posil = temp_posil;
      //        continue;
      //      }
      //      }
      if (TOF_R < 200 && digitalRead(wall_detector_right) == 0)
      {
        if ((posil + posir) / 2 < 0.5 * tile_length)
          read_Cameras(X_Position, Y_Position);
        else
        {
          if (Direction == 0)
            read_Cameras(X_Position, Y_Position + 1);
          else if (Direction == 1)
            read_Cameras(X_Position + 1, Y_Position);
          else if (Direction == 2)
            read_Cameras(X_Position, Y_Position - 1);
          else
            read_Cameras(X_Position - 1, Y_Position);
        }
      }
      if (TOF_R < 70)
      { // adjust quickly to the left
        int temp_posil = posil;
        int temp_posir = posir;
        while (TOF_R < 73) { // to turn till the reading of the right TOF is 78
          MoveWheels(LOW, 200, HIGH, 200, "Left");//LOW, 200, HIGH, 200, "Left"
          read_all_TOFs();
          //read_Cameras();
        }
        posir = temp_posir;
        posil = temp_posil;
      }
      else if ((TOF_R > 85) && (TOF_R <= 105)) // 135 // adjust the robot to turn right slightly
      {
        //read_Cameras();
        pwm_L = max(174, 174 + ((TOF_R - 85) / 50.0) * 80.0);
        pwm_R = max(200, 200 - ((TOF_R - 85) / 50.0) * 54.0);
      }
      else if ((TOF_R > 105) && (TOF_R <= 200)) // adjust robot to turn right sharply
      {
        //read_Cameras();
        pwm_L = 250;
        pwm_R = 174;
      }
      else { // robot moves in a straight line
        pwm_R = 200;
        pwm_L = 193;
      }
      if (digitalRead(wall_detector_right) && right_counter == 0 && TOF_R >= 200) // TOF_R >= 200
      {
        right_counter++;
        posir_tmp = posir;
        posil_tmp = posil;
      }
      else if (digitalRead(wall_detector_right) && TOF_R >= 200)
      {
        if (((posil + posir) / 2) - ((posil_tmp + posir_tmp) / 2) >= 750)
        {
          Add_Tile();
          Move('R', 0, turn_angle_R);
          Move('X', 2600, 0);
          break;
        }
      }
      else
      {
        right_counter = 0;
        posir_tmp = posir;
        posil_tmp = posil;
      }
      MoveWheels(HIGH, pwm_L, HIGH, pwm_R, "Forward");
    } // end of while loop

    if ((posil + posir) / 2 >= 0.5 * tile_length)
      Add_Tile();
    timer = millis();
    while (millis() - timer <= 500) { // wait half a second
      read_all_TOFs();
      if (TOF_R <= 200 && digitalRead(wall_detector_right) == 0)//
      {
        if ((posil + posir) / 2 < 0.5 * tile_length)
          read_Cameras(X_Position, Y_Position);
        else
        {
          if (Direction == 0)
            read_Cameras(X_Position, Y_Position + 1);
          else if (Direction == 1)
            read_Cameras(X_Position + 1, Y_Position);
          else if (Direction == 2)
            read_Cameras(X_Position, Y_Position - 1);
          else
            read_Cameras(X_Position - 1, Y_Position);
        }
      }
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
    //    tile_length = 2330;
    posir = 0;
    posil = 0;
    left_turn = 0;
  }
  else if (movement_dir == 'X') { // if the robot has to move forward according to the right hand rule
    while ((((posir + posil) / 2) <= (tile_length * 1)) && (TOF_C > 85)) { // to move one tile forward
      if (tilt && digitalRead(tilt_asc) == 0)
      {
        tilt = 0;
        tile_length += 100;
      }
      else if (digitalRead(tilt_asc) == 1) {
        tilt = 1;
      }
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;

      if (!isBlack())
      {
        black_counter = 0;
      }
      else
        black_counter++;

      if ((isBlue()) && !(blue_flag) && blue_counter >= 4000) {
        timer = millis();
        while (millis() - timer <= 5000) { // wait half a second
          read_all_TOFs();
          MoveWheels(HIGH, 0, HIGH, 0, "Stop");
        }
        blue_flag = 1;
        blue_counter = 0;
      }
      read_all_TOFs();
      if (isBlack() && black_counter >= 50) {
        //        int temp_posil = posil, temp_posir = posir;
        posil = 0;
        posir = 0;
        while (((posir + posil) / 2) >= -1200) {
          MoveWheels(LOW, 200, LOW, 200, "Back");
        }
        //        Move('R');
        //        Move('R');
        Move('L', 0, 2950);
        read_all_TOFs();
        if (TOF_C < 150) {
          Move('L', 0, 2950);
        }
        else {
          //            tile_length = 2500;
          Move('X', 2650, 0);
        }
        black_counter = 0;
        return ;
      }
      if (digitalRead(ir_obstacle_left) == 0 && TOF_C > 200) {
        int temp_posil = posil;
        int temp_posir = posir;
        while (digitalRead(ir_obstacle_left) == 0) { // to turn till the reading of the right TOF is 78
          MoveWheels(HIGH, 200, LOW, 200, "RIGHT");//LOW, 200, HIGH, 200, "Left"
          read_all_TOFs();
          if (TOF_R < 200 && digitalRead(wall_detector_right) == 0)
          {
            if ((posil + posir) / 2 < 0.5 * tile_length)
              read_Cameras(X_Position, Y_Position);
            else
            {
              if (Direction == 0)
                read_Cameras(X_Position, Y_Position + 1);
              else if (Direction == 1)
                read_Cameras(X_Position + 1, Y_Position);
              else if (Direction == 2)
                read_Cameras(X_Position, Y_Position - 1);
              else
                read_Cameras(X_Position - 1, Y_Position);
            }
          }
          //read_Cameras();
        }
        posir = temp_posir;
        posil = temp_posil;
        continue;
      }
      //      if (digitalRead(ir_obstacle_right) == 0 && TOF_C > 200) {
      //        int temp_posil = posil;
      //        int temp_posir = posir;
      //        while (digitalRead(ir_obstacle_right) == 0) { // to turn till the reading of the right TOF is 78
      //          MoveWheels(LOW, 200, HIGH, 200, "LEFT");//LOW, 200, HIGH, 200, "Left"
      //          read_all_TOFs();
      //          if (TOF_R < 200 && digitalRead(wall_detector_right) == 0)
      //            read_Cameras();
      //          //read_Cameras();
      //        }
      //        posir = temp_posir;
      //        posil = temp_posil;
      //        continue;
      //      }
      if (TOF_R < 200 && digitalRead(wall_detector_right) == 0)
      {
        if ((posil + posir) / 2 < 0.5 * tile_length)
          read_Cameras(X_Position, Y_Position);
        else
        {
          if (Direction == 0)
            read_Cameras(X_Position, Y_Position + 1);
          else if (Direction == 1)
            read_Cameras(X_Position + 1, Y_Position);
          else if (Direction == 2)
            read_Cameras(X_Position, Y_Position - 1);
          else
            read_Cameras(X_Position - 1, Y_Position);
        }
      }
      if (TOF_R < 70)
      { // adjust quickly to the left
        int temp_posil = posil;
        int temp_posir = posir;
        while (TOF_R < 73) { // to turn till the reading of the right TOF is 78
          MoveWheels(LOW, 200, HIGH, 200, "Left");//LOW, 200, HIGH, 200, "Left"
          read_all_TOFs();
          //read_Cameras();
        }
        posir = temp_posir;
        posil = temp_posil;
      }
      else if ((TOF_R > 85) && (TOF_R <= 105)) // 135 // adjust the robot to turn right slightly
      {
        //read_Cameras();
        pwm_L = max(174, 174 + ((TOF_R - 85) / 50.0) * 80.0);
        pwm_R = max(200, 200 - ((TOF_R - 85) / 50.0) * 54.0);
      }
      else if ((TOF_R > 105) && (TOF_R <= 200)) // adjust robot to turn right sharply
      {
        //read_Cameras();
        pwm_L = 250;
        pwm_R = 174;
      }
      else { // robot moves in a straight line
        pwm_R = 200;
        pwm_L = 193;
      }
      MoveWheels(HIGH, pwm_L, HIGH, pwm_R, "Forward");
    } // end of while loop
    if ((posil + posir) / 2 >= 0.6 * tile_length)
      Add_Tile();
    timer = millis();
    while (millis() - timer <= 500) { // wait half a second
      read_all_TOFs();
      if (TOF_R <= 200 && digitalRead(wall_detector_right) == 0)//
      {
        if ((posil + posir) / 2 < 0.5 * tile_length)
          read_Cameras(X_Position, Y_Position);
        else
        {
          if (Direction == 0)
            read_Cameras(X_Position, Y_Position + 1);
          else if (Direction == 1)
            read_Cameras(X_Position + 1, Y_Position);
          else if (Direction == 2)
            read_Cameras(X_Position, Y_Position - 1);
          else
            read_Cameras(X_Position - 1, Y_Position);
        }
      }
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
    //    tile_length = 2330;
    posir = 0;
    posil = 0;
    left_turn = 0;
  }

  else if (movement_dir == 'Y') { // if the robot has to move forward according to the right hand rule
    while ((((posir + posil) / 2) <= (tile_length * 1)) && (TOF_C > 85)) { // to move one tile forward
      if (tilt && digitalRead(tilt_asc) == 0)
      {
        tilt = 0;
        tile_length += 100;
      }
      else if (digitalRead(tilt_asc) == 1) {
        tilt = 1;
      }
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;

      if (!isBlack())
      {
        black_counter = 0;
      }
      else
        black_counter++;

      if ((isBlue()) && !(blue_flag) && blue_counter >= 4000) {
        timer = millis();
        while (millis() - timer <= 5000) { // wait half a second
          read_all_TOFs();
          MoveWheels(HIGH, 0, HIGH, 0, "Stop");
        }
        blue_flag = 1;
        blue_counter = 0;
      }
      read_all_TOFs();
      if (isBlack() && black_counter >= 50) {
        //        int temp_posil = posil, temp_posir = posir;
        posil = 0;
        posir = 0;
        while (((posir + posil) / 2) >= -1200) {
          MoveWheels(LOW, 200, LOW, 200, "Back");
        }
        //        Move('R');
        //        Move('R');
        Move('L', 0, 2950);
        read_all_TOFs();
        if (TOF_C < 150) {
          Move('L', 0, 2950);
        }
        else {
          //            tile_length = 2500;
          Move('X', 2650, 0);
        }
        black_counter = 0;
        return ;
      }
      if (digitalRead(ir_obstacle_left) == 0 && TOF_C > 200) {
        int temp_posil = posil;
        int temp_posir = posir;
        while (digitalRead(ir_obstacle_left) == 0) { // to turn till the reading of the right TOF is 78
          MoveWheels(HIGH, 200, LOW, 200, "RIGHT");//LOW, 200, HIGH, 200, "Left"
          read_all_TOFs();
          if (TOF_R < 200 && digitalRead(wall_detector_right) == 0)
          {
            if ((posil + posir) / 2 < 0.5 * tile_length)
              read_Cameras(X_Position, Y_Position);
            else
            {
              if (Direction == 0)
                read_Cameras(X_Position, Y_Position + 1);
              else if (Direction == 1)
                read_Cameras(X_Position + 1, Y_Position);
              else if (Direction == 2)
                read_Cameras(X_Position, Y_Position - 1);
              else
                read_Cameras(X_Position - 1, Y_Position);
            }
          }
          //read_Cameras();
        }
        posir = temp_posir;
        posil = temp_posil;
        continue;
      }
      if (digitalRead(ir_obstacle_right) == 0 && TOF_C > 200) {
        int temp_posil = posil;
        int temp_posir = posir;
        while (digitalRead(ir_obstacle_right) == 0) { // to turn till the reading of the right TOF is 78
          MoveWheels(LOW, 200, HIGH, 200, "LEFT");//LOW, 200, HIGH, 200, "Left"
          read_all_TOFs();
          if (TOF_R < 200 && digitalRead(wall_detector_right) == 0)
          {
            if ((posil + posir) / 2 < 0.5 * tile_length)
              read_Cameras(X_Position, Y_Position);
            else
            {
              if (Direction == 0)
                read_Cameras(X_Position, Y_Position + 1);
              else if (Direction == 1)
                read_Cameras(X_Position + 1, Y_Position);
              else if (Direction == 2)
                read_Cameras(X_Position, Y_Position - 1);
              else
                read_Cameras(X_Position - 1, Y_Position);
            }
          }
          //read_Cameras();
        }
        posir = temp_posir;
        posil = temp_posil;
        continue;
      }
      if (TOF_R < 200 && digitalRead(wall_detector_right) == 0)
      {
        if ((posil + posir) / 2 < 0.5 * tile_length)
          read_Cameras(X_Position, Y_Position);
        else
        {
          if (Direction == 0)
            read_Cameras(X_Position, Y_Position + 1);
          else if (Direction == 1)
            read_Cameras(X_Position + 1, Y_Position);
          else if (Direction == 2)
            read_Cameras(X_Position, Y_Position - 1);
          else
            read_Cameras(X_Position - 1, Y_Position);
        }
      }
      if (TOF_R < 70)
      { // adjust quickly to the left
        int temp_posil = posil;
        int temp_posir = posir;
        while (TOF_R < 73) { // to turn till the reading of the right TOF is 78
          MoveWheels(LOW, 200, HIGH, 200, "Left");//LOW, 200, HIGH, 200, "Left"
          read_all_TOFs();
          //read_Cameras();
        }
        posir = temp_posir;
        posil = temp_posil;
      }
      else if ((TOF_R > 85) && (TOF_R <= 105)) // 135 // adjust the robot to turn right slightly
      {
        //read_Cameras();
        pwm_L = max(174, 174 + ((TOF_R - 85) / 50.0) * 80.0);
        pwm_R = max(200, 200 - ((TOF_R - 85) / 50.0) * 54.0);
      }
      else if ((TOF_R > 105) && (TOF_R <= 200)) // adjust robot to turn right sharply
      {
        //read_Cameras();
        pwm_L = 250;
        pwm_R = 174;
      }
      else { // robot moves in a straight line
        pwm_R = 200;
        pwm_L = 193;
      }
      MoveWheels(HIGH, pwm_L, HIGH, pwm_R, "Forward");
    } // end of while loop
    Add_Tile();
    timer = millis();
    while (millis() - timer <= 500) { // wait half a second
      read_all_TOFs();
      if (TOF_R <= 200 && digitalRead(wall_detector_right) == 0)//
      {
        if ((posil + posir) / 2 < 0.5 * tile_length)
          read_Cameras(X_Position, Y_Position);
        else
        {
          if (Direction == 0)
            read_Cameras(X_Position, Y_Position + 1);
          else if (Direction == 1)
            read_Cameras(X_Position + 1, Y_Position);
          else if (Direction == 2)
            read_Cameras(X_Position, Y_Position - 1);
          else
            read_Cameras(X_Position - 1, Y_Position);
        }
      }
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
    //    tile_length = 2330;
    posir = 0;
    posil = 0;
    left_turn = 0;
  }
  else if (movement_dir == 'R') {
    //    Serial.print("wall_detector_right: ");
    //    Serial.println(digitalRead(wall_detector_right));
    //    while (digitalRead(wall_detector_right) == 0)
    //    {
    //      MoveWheels(HIGH, 193, HIGH, 200, "Forward");
    //    }
    posil = 0;
    posir = 0;
    while (abs(posir - posil) <= turn_angle) { // turn 90 degrees to the right
      //read_Cameras();
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;
      if(digitalRead(ir_obstacle_right) == 0 && (abs(posir - posil) / turn_angle) > 0.7)
        break;
      MoveWheels(HIGH, 200, LOW, 200, "Right");
    }
    Change_Direction('R');
    timer = millis();
    while (millis() - timer <= 500) { // wait half a second
      read_all_TOFs();
      //read_Cameras();
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    //    tile_length = 2500;
    posir = 0;
    posil = 0;
    left_turn = 0;
  }
  else {
    posir = 0;
    posil = 0;
    while (abs(posir - posil) <= turn_angle) { // turn 90 degrees to the left
      read_Cameras(X_Position, Y_Position);
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;
      MoveWheels(LOW, 200, HIGH, 200, "Left");
    }
    Change_Direction('L');
    timer = millis();
    while (millis() - timer <= 500) { // wait half a second
      read_all_TOFs();
      read_Cameras(X_Position, Y_Position);
      if (!isBlue())
      {
        blue_flag = 0;
        blue_counter = 0;
      }
      else
        blue_counter++;
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    //    tile_length = 2330;
    if (left_turn) {
      //      tile_length = 2200;
    }
    posir = 0;
    posil = 0;
    left_turn = 1;
  }
}
