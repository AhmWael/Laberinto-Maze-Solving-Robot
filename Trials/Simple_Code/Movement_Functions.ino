void MoveWheels (bool dir_l, int speed_l, bool dir_r, int speed_r, String to_print) {
  digitalWrite(l_dir, !(dir_l));
  analogWrite(l_pwm, speed_l);
  digitalWrite(r_dir, !(dir_r));
  analogWrite(r_pwm, speed_r);
  //Serial.println(to_print);
}

void Move(char movement_dir) {
  read_all_TOFs();
  if (movement_dir == 'F') {
    while ((((posir + posil2) / 2) <= (tile_length * 1)) && (TOF_C > 70)) {
      read_all_TOFs();
      if (TOF_R <= 85)
      {
        pwm_L = max(94, 94 + ((TOF_R - 35) / 50.0) * 80.0);
        pwm_R = min(254, 254 - ((TOF_R - 35) / 50.0) * 54.0);
      }
      else if ((TOF_R > 85) && (TOF_R <= 135))
      {
        pwm_L = max(174, 174 + ((TOF_R - 85) / 50.0) * 80.0);
        pwm_R = max(200, 200 - ((TOF_R - 85) / 50.0) * 54.0);
      }
      else if ((TOF_R > 135) && (TOF_R <= 200))
      {
        pwm_L = 250;
        pwm_R = 174;
      }
      else {
        pwm_R = 200;
        pwm_L = 193;
      }
      MoveWheels(HIGH, pwm_L, HIGH, pwm_R, "Forward");
            Serial.print("TOF_L:");
            Serial.print(TOF_L);
            Serial.print("TOF_R:");
            Serial.print(TOF_R);
            Serial.print("\t");
            Serial.print("Left PWM: ");
            Serial.print(pwm_L);
            Serial.print("     ");
            Serial.print("Right PWM: ");
            Serial.print(pwm_R);
            Serial.println();
      Serial.print("posil : ");
      Serial.print(posil);
      Serial.print("\tposir : ");
      Serial.println(posir);
    }
    //    Serial.println("##################################");
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 500) {
      read_all_TOFs();
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    Serial.println("New Tile Reached");
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
    tile_length = 1200;
    posir = 0;
    posil = 0;
    while (abs(posir - posil) <= 2750) {
      MoveWheels(HIGH, 200, LOW, 200, "Right");
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
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    Serial.println("##################################");
    Serial.println("New Tile Reached");
    tile_length = 1200;
    posir = 0;
    posil = 0;
  }
  else {
    while (abs(posir - posil) <= 2750) {
      MoveWheels(LOW, 200, HIGH, 200, "Left");
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
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    Serial.println("##################################");
    Serial.println("New Tile Reached");
    tile_length = 1200;
    posir = 0;
    posil = 0;
  }
}
