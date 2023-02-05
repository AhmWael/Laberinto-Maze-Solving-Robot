void MoveWheels (bool dir_l, int speed_l, bool dir_r, int speed_r, String to_print) {
  digitalWrite(l_dir, dir_l);
  analogWrite(l_pwm, speed_l);
  digitalWrite(r_dir, dir_r);
  analogWrite(r_pwm, speed_r);
  //Serial.println(to_print);
}



void Move(char movement_dir) {
  read_all_TOFs();
  if (movement_dir == 'F') {
    while ((((posir + posil2) / 2) <= (tile_length * 1)) && (TOF_C > 70)) {
      read_all_TOFs();
      read_Cameras();
      if (isBlack() == true) {
        while (((posir + posil2) / 2) > 0) {
          //MoveWheels(HIGH, 200, HIGH, 200, "Back");
          MoveWheels_auto(200, 200, 'b');
        }
        Move('R');
        Move('R');
        
       
      }
      if (TOF_R < 85)
      {
        int temp_posil = posil2;
        int temp_posir = posir;
        while (TOF_R < 85) {
          //MoveWheels(LOW, 200, HIGH, 200, "Left");//LOW, 200, HIGH, 200, "Left"
          MoveWheels_auto(200, 200, 'l');
          read_all_TOFs();
          read_Cameras();
        }
        posir = temp_posir;
        posil2 = temp_posil;
        //        pwm_L = max(94, 94 + ((TOF_R - 35) / 50.0) * 80.0);
        //        pwm_R = min(254, 254 - ((TOF_R - 35) / 50.0) * 54.0);
      }
      else if ((TOF_R >= 85) && (TOF_R <= 105))//135
      {
        pwm_L = max(174, 174 + ((TOF_R - 85) / 50.0) * 80.0);
        pwm_R = max(200, 200 - ((TOF_R - 85) / 50.0) * 54.0);
//        Serial.println("Here 1");
      }
      else if ((TOF_R > 105) && (TOF_R <= 200))//135    200
      {
        pwm_L = 250;
        pwm_R = 174;
//        Serial.println("Here 2");
      }
      else {
        pwm_R = 200;
        pwm_L = 193;
      }
      //MoveWheels(LOW, pwm_L, LOW, pwm_R, "Forward");//HIGH, pwm_L, HIGH, pwm_R, "Forward"
      MoveWheels_auto(pwm_L, pwm_R, 'f');
      
//      Serial.print("TOF_C:");
//      Serial.print(TOF_C);
//      Serial.print("\tTOF_R:");
//      Serial.print(TOF_R);
//      Serial.print("\t");
      //      Serial.print("Left PWM: ");
      //      Serial.print(pwm_L);
      //      Serial.print("     ");
      //      Serial.print("Right PWM: ");
      //      Serial.print(pwm_R);
//      Serial.println();
      //      Serial.print("posil : ");
      //      Serial.print(posil);
      //      Serial.print("\tposir : ");
      //      Serial.println(posir);
    }
    //    Serial.println("##################################");
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 500) {
      read_all_TOFs();
      //read_Cameras();
      //MoveWheels(LOW, 0, LOW, 0, "Stop");
      MoveWheels_auto(0, 0, 's');

    }
//    Serial.println("New Tile Reached");
    general_pwm = -1;
    //    Serial.print("posir: ");
    //    Serial.print(posir);
    //    Serial.print("\tposil: ");
    //    Serial.println(posil);
    tile_length = 1000;
    posir = 0;
    posil = 0;
    //tile ++;
  }
  else if (movement_dir == 'R') {
    tile_length = 1000;
    posir = 0;
    posil = 0;
    while (abs(posir - posil) <= 2800) {//2750
      //MoveWheels(HIGH, 200, LOW, 200, "Right");//HIGH, 200, LOW, 200, "Right"
      MoveWheels_auto(200, 200, 'r');
      //      Serial.print("TOF_C:");
      //      Serial.print(TOF_C);
      //      Serial.print("\tTOF_R:");
      //      Serial.println(TOF_R);

    }
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 500) {
      read_all_TOFs();
//      read_Cameras();
      //MoveWheels(LOW, 0, LOW, 0, "Stop");
      MoveWheels_auto(0, 0, 's');

    }
//    Serial.println("##################################");
//    Serial.println("New Tile Reached");
    tile_length = 1000;
    posir = 0;
    posil = 0;
  }
  else {
    while (abs(posir - posil) <= 2850) {//2750
      //MoveWheels(LOW, 200, HIGH, 200, "Left");//LOW, 200, HIGH, 200, "Left"
      MoveWheels_auto(200, 200, 'l');
      //      Serial.print("TOF_C:");
      //      Serial.print(TOF_C);
      //      Serial.print("\tTOF_R:");
      //      Serial.println(TOF_R);

    }
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 500) {
      read_all_TOFs();
      read_Cameras();
      //MoveWheels(LOW, 0, LOW, 0, "Stop");
      MoveWheels_auto(0, 0, 's');

    }
//    Serial.println("##################################");
//    Serial.println("New Tile Reached");
    tile_length = 1000;
    posir = 0;
    posil = 0;
  }
}

void MoveWheels_auto (int speed_l, int speed_r, char movement) {
  if (movement == 'f')
  {
    //MoveWheels_auto(200, 200, "f");
    digitalWrite(l_dir, LOW);
    analogWrite(l_pwm, speed_l);
    digitalWrite(r_dir, LOW);
    analogWrite(r_pwm, speed_r);
  }
  else if (movement == 'r')
  {
    //MoveWheels_auto(200, 200, "r");
    digitalWrite(l_dir, HIGH);
    analogWrite(l_pwm, speed_l);
    digitalWrite(r_dir, LOW);
    analogWrite(r_pwm, speed_r);
  }
  else if (movement == 'l')
  {
    //MoveWheels_auto(200, 200, "l");
    digitalWrite(l_dir, LOW);
    analogWrite(l_pwm, speed_l);
    digitalWrite(r_dir, HIGH);
    analogWrite(r_pwm, speed_r);
  }
  else if (movement == 'b')
  {
    //MoveWheels_auto(200, 200, "b");
    digitalWrite(l_dir, HIGH);
    analogWrite(l_pwm, speed_l);
    digitalWrite(r_dir, HIGH);
    analogWrite(r_pwm, speed_r);
  }
  else if (movement == 's')
  {
    //MoveWheels_auto(200, 200, "b");
    digitalWrite(l_dir, HIGH);
    analogWrite(l_pwm, 0);
    digitalWrite(r_dir, HIGH);
    analogWrite(r_pwm, 0);
  }
  //  digitalWrite(l_dir, dir_l);
  //  analogWrite(l_pwm, speed_l);
  //  digitalWrite(r_dir, dir_r);
  //  analogWrite(r_pwm, speed_r);
  //Serial.println(to_print);
}
