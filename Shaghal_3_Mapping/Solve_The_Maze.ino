void Solve() {
//  if (x_maze == 30 && y_maze == 30 && started == 1 && robot_dir == 0) {
//    started = -1;
//    for (int x = x_min - 1; x <= x_max + 1; x ++) {
//      for (int y = y_min - 1; y <= y_max + 1; y ++) {
//        Serial.print(maze[x][y]);
//      }
//      Serial.println();
//    }
//    Serial.println(F("######################################"));
//    return ;
//  }
//  search_for_walls();
//  maze[x_maze][y_maze] = 'V';

  read_all_TOFs();
  read_Cameras();
  read_Color();
  if (isBlue() == true) {
    timer = millis();
    while (millis() - timer <= 5000) {
      read_all_TOFs();
      read_Cameras();
      MoveWheels(LOW, 0, LOW, 0, "Stop");

    }
  }
//    Serial.print("TOF_C:");
//    Serial.print(TOF_C);
//    Serial.print("\tTOF_R:");
//    Serial.println(TOF_R);

//    Serial.print("posil: ");
//    Serial.print(posil);
//    Serial.print("\tposir:");
//    Serial.println(posir);

//    MoveWheels(HIGH, 174, HIGH, 200, "Forward");

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
