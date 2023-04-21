void read_Cameras(int X_Pos, int Y_Pos) {
  Cam_1_R = digitalRead(Cam_1_R_pin);
  Cam_2_R = digitalRead(Cam_2_R_pin);
  Cam_3_R = digitalRead(Cam_3_R_pin);
  //  Serial.print(Cam_1_R);
  //  Serial.print(F("     "));
  //  Serial.print(Cam_2_R);
  //  Serial.print(F("     "));
  //  Serial.println(Cam_3_R);
  if (Cam_1_R == 0 && Cam_2_R == 0 && Cam_3_R == 0) {
    //Serial.println(" Right Camera Serial --> Nothing_Cam_1 ");
  }
  else if (Cam_1_R == 0 && Cam_2_R == 1 && Cam_3_R == 0 && Maze[X_Pos][Y_Pos][5] != 1) {
    //    Serial.println(" Right Camera Serial --> Green Found ");
    //Save Positiion of Victim with current direction
    Maze[X_Pos][Y_Pos][5] = 1;
    deploy_kit('r', 0);
  }
  else if (Cam_1_R == 0 && Cam_2_R == 1 && Cam_3_R == 1 && Maze[X_Pos][Y_Pos][5] != 1) {
    //    Serial.println(" Right Camera Serial --> Yellow Found ");
    //Save Positiion of Victim with current direction
    Maze[X_Pos][Y_Pos][5] = 1;
    deploy_kit('r', 1);
  }
  else if (Cam_1_R == 1 && Cam_2_R == 0 && Cam_3_R == 0 && Maze[X_Pos][Y_Pos][5] != 1) {
    //    Serial.println(" Right Camera Serial --> Red Found ");
    //Save Positiion of Victim with current direction
    Maze[X_Pos][Y_Pos][5] = 1;
    deploy_kit('r', 1);
  }
  else if (Cam_1_R == 1 && Cam_2_R == 0 && Cam_3_R == 1 && Maze[X_Pos][Y_Pos][5] != 1) {
    //    Serial.println(" Right Camera Serial --> U Found ");
    //Save Positiion of Victim with current direction
    Maze[X_Pos][Y_Pos][5] = 1;
    deploy_kit('r', 0);
  }
  else if (Cam_1_R == 1 && Cam_2_R == 1 && Cam_3_R == 0 && Maze[X_Pos][Y_Pos][5] != 1) {
    //    Serial.println(" Right Camera Serial --> S Found ");
    //Save Positiion of Victim with current direction
    Maze[X_Pos][Y_Pos][5] = 1;
    deploy_kit('r', 2);
  }
  else if (Cam_1_R == 0 && Cam_2_R == 0 && Cam_3_R == 1 && Maze[X_Pos][Y_Pos][5] != 1) {
    //    Serial.println(" Right Camera Serial --> H Found ");
    //Save Positiion of Victim with current direction
    Maze[X_Pos][Y_Pos][5] = 1;
    deploy_kit('r', 3);
  }
}
