void read_Cameras() {

  //  Cam_1_L = digitalRead(Cam_1_L_pin);
  //  Cam_2_L = digitalRead(Cam_2_L_pin);
  //  Cam_3_L = digitalRead(Cam_3_L_pin);
  Cam_1_R = digitalRead(Cam_1_R_pin);
  Cam_2_R = digitalRead(Cam_2_R_pin);
  Cam_3_R = digitalRead(Cam_3_R_pin);
  //Serial.print("Cam_1_R: ");
  //Serial.print(Cam_1_R);
  //Serial.print("\tCam_2_R: ");
  //Serial.print(Cam_2_R);
  //Serial.print("\tCam_3_R: ");
  //Serial.println(Cam_3_R);
  
//  if (Cam_1_R == 1 || Cam_2_R == 1 || Cam_3_R == 1){
//    Serial.println(" Right Camera Serial --> U Found ");
//    timer = millis();
//    //      Serial.print(millis());
//    //      Serial.print("\t");
//    //      Serial.println(timer);
//    while (millis() - timer <= 4000) {
//      Serial.println((int)timer);
//      read_all_TOFs();
//      digitalWrite(buzzer, HIGH);
//      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
//    }
//    Serial.println("New Tile Reached");
//    digitalWrite(buzzer, LOW);
//  }
//  else if (Cam_1_R == 1 && Cam_2_R == 1 && Cam_3_R == 1) {
//    Serial.println(" Right Camera Serial --> Nothing_Cam_2 ");
//  }
  if (Cam_1_R == 0 && Cam_2_R == 0 && Cam_3_R == 0) {
    //Serial.println(" Right Camera Serial --> Nothing_Cam_1 ");
  }
  else if (Cam_1_R == 0 && Cam_2_R == 1 && Cam_3_R == 0) {
    //Serial.println(" Right Camera Serial --> Green Found ");
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 4000) {
//      Serial.println((int)timer);
      read_all_TOFs();
      digitalWrite(buzzer, HIGH);
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
//    Serial.println("New Tile Reached");
    digitalWrite(buzzer, LOW);
  }
  else if (Cam_1_R == 0 && Cam_2_R == 1 && Cam_3_R == 1) {
    //Serial.println(" Right Camera Serial --> Yellow Found ");
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 4000) {
//      Serial.println((int)timer);
      read_all_TOFs();
      digitalWrite(buzzer, HIGH);
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
//    Serial.println("New Tile Reached");
    digitalWrite(buzzer, LOW);
  }
  else if (Cam_1_R == 1 && Cam_2_R == 0 && Cam_3_R == 0) {
    //Serial.println(" Right Camera Serial --> Red Found ");
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 4000) {
//      Serial.println((int)timer);
      read_all_TOFs();
      digitalWrite(buzzer, HIGH);
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
//    Serial.println("New Tile Reached");
    digitalWrite(buzzer, LOW);
  }
  else if (Cam_1_R == 1 && Cam_2_R == 0 && Cam_3_R == 1) {
    //Serial.println(" Right Camera Serial --> U Found ");
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 4000) {
//      Serial.println((int)timer);
      read_all_TOFs();
      digitalWrite(buzzer, HIGH);
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
//    Serial.println("New Tile Reached");
    digitalWrite(buzzer, LOW);
  }
  else if (Cam_1_R == 1 && Cam_2_R == 1 && Cam_3_R == 0) {
    //Serial.println(" Right Camera Serial --> S Found ");
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 2000) {
//      Serial.println(timer);
      read_all_TOFs();
      digitalWrite(buzzer, HIGH);
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
//    Serial.println("New Tile Reached");
    digitalWrite(buzzer, LOW);
  }
  else if (Cam_1_R == 0 && Cam_2_R == 0 && Cam_3_R == 1) {
    //Serial.println(" Right Camera Serial --> H Found ");
    timer = millis();
    //      Serial.print(millis());
    //      Serial.print("\t");
    //      Serial.println(timer);
    while (millis() - timer <= 2000) {
//      Serial.println((int)timer);
      read_all_TOFs();
      digitalWrite(buzzer, HIGH);
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
//    Serial.println("New Tile Reached");
    digitalWrite(buzzer, LOW);
  }

  //  if(Cam_1_L == 0 && Cam_2_L == 0 && Cam_3_L == 0){ Serial.println(" Left Camera Serial --> Nothing_Cam_1 "); }
  //  else if(Cam_1_L == 0 && Cam_2_L == 0 && Cam_3_L == 1){ Serial.println(" Left Camera Serial --> Nothing_Cam_2 "); }
  //  else if(Cam_1_L == 0 && Cam_2_L == 1 && Cam_3_L == 0){ Serial.println(" Left Camera Serial --> Green Found "); }
  //  else if(Cam_1_L == 0 && Cam_2_L == 1 && Cam_3_L == 1){ Serial.println(" Left Camera Serial --> Yellow Found "); }
  //  else if(Cam_1_L == 1 && Cam_2_L == 0 && Cam_3_L == 0){ Serial.println(" Left Camera Serial --> Red Found "); }
  //  else if(Cam_1_L == 1 && Cam_2_L == 0 && Cam_3_L == 1){ Serial.println(" Left Camera Serial --> U Found "); }
  //  else if(Cam_1_L == 1 && Cam_2_L == 1 && Cam_3_L == 0){ Serial.println(" Left Camera Serial --> S Found "); }
  //  else if(Cam_1_L == 1 && Cam_2_L == 1 && Cam_3_L == 1){ Serial.println(" Left Camera Serial --> H Found "); }

}
