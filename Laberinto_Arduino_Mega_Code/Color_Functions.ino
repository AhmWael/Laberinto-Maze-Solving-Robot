void read_Color () {

  Col_1 = digitalRead(Col_1_pin);
  Col_2 = digitalRead(Col_2_pin);

  if (Col_1 == 0 && Col_2 == 0) {
    Serial.println(" Color Serial --> Nothing_Color_1 ");
  }
  else if (Col_1 == 0 && Col_2 == 1) {
    Serial.println(" Color Serial --> Blue Floor Found ");
  }
  else if (Col_1 == 1 && Col_2 == 0) {
    Serial.println(" Color Serial --> Silver Floor Found ");
  }
  else if (Col_1 == 1 && Col_2 == 1) {
    Serial.println(" Color Serial --> Black Floor Found ");
    //    MoveWheels(LOW, 0, HIGH, 0, "Stop");
  }
}

bool isBlack () {
  // This function reads the Color Pins and compares them to predetermined values that match the ones that are sent by the Arduino Nano
  // it returns true if black is detected otherwise it returns false
  
  Col_1 = digitalRead(Col_1_pin);
  Col_2 = digitalRead(Col_2_pin);

  if (Col_1 == 1 && Col_2 == 1) {
    Serial.println(" Color Serial --> Black Floor Found ");
    // This for loop is used to block the the black tile (make it completely unaccessible) and mark the black tile as a visited tile according to the direction
    for (int i = 0; i < 4; i++)
    {
      if (Direction == 0)
      {
        Maze[X_Position][Y_Position + 1][i] = 1;
        Maze[X_Position + 1][Y_Position][4] = 1;
      }
      else if (Direction == 1)
      {
        Maze[X_Position + 1][Y_Position][i] = 1;
        Maze[X_Position + 1][Y_Position][4] = 1;
      }
      else if (Direction == 2)
      {
        Maze[X_Position][Y_Position - 1][i] = 1;
        Maze[X_Position][Y_Position - 1][4] = 1;
      }
      else if (Direction == 3)
      {
        Maze[X_Position - 1][Y_Position][i] = 1;
        Maze[X_Position - 1][Y_Position][4] = 1;
      }
    }

    //MoveWheels(LOW, 0, HIGH, 0, "Stop");
    return true;
  }
  else {
    return false;
  }
}

bool isBlue() {
  // This function reads the Color Pins and compares them to predetermined values that match the ones that are sent by the Arduino Nano
  // it returns true if blue is detected otherwise it returns false
  
  Col_1 = digitalRead(Col_1_pin);
  Col_2 = digitalRead(Col_2_pin);

  if (Col_1 == 0 && Col_2 == 1) {
    //Serial.println(" Color Serial --> Blue Floor Found ");
    return true;
  }
  else {
    return false;
  }
}
