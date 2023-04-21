void Solve() {
  read_all_TOFs();
  right_counter = 0;
  //read_Cameras();
  //for testing TOF
  //  Serial.print("TOF_C:");
  //  Serial.print(TOF_C);
  //  Serial.print("\tTOF_R:");
  //  Serial.println(TOF_R);

  //  MoveWheels(HIGH, 200, HIGH, 200, "Forward");
  //  Serial.print(F("posil = "));
  //  Serial.print(posil);
  //  Serial.print(F("   posir = "));
  //  Serial.print(posir);
  //  Serial.println();
  if (!isBlack())
  {
    black_counter = 0;
  }
  else
    black_counter++;

  if (!isBlue())
  {
    blue_flag = 0;
    blue_counter = 0;
  }
  else
    blue_counter++;
  if ((isBlue()) && !(blue_flag) && blue_counter >= 4000) {
    timer = millis();
    while (millis() - timer <= 5000) { // wait half a second
      read_all_TOFs();
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    blue_flag = 1;
    blue_counter = 0;
  }
  else if (X_Position == 20 && Y_Position == 20 && Direction == 0 && !Start_Tile)
  {
    timer = millis();
    while(millis() - timer <= 10000)
    {
      read_all_TOFs();
      MoveWheels(LOW, 0, LOW, 0, "STOP");
    }
    Serial.println(Minimum_X);
    Serial.println(Minimum_Y);
    Serial.println(Maximum_X);
    Serial.println(Maximum_Y);

    int sizee = 2 * Size();
    while (Size() != 0) // && Check_Unvisited_Availability(sizee)
    {
      Generate_unvisited_array();
      Sort_Unvisited(2 * Size());
      if(Check_Unvisited_Availability(2 * Size()) == 0)
        break;
      for(int i = 0; i < 2*Size(); i+=2)
      {
        Serial.print(Unvisited[i]);
        Serial.print("\t");
        Serial.print(Unvisited[i + 1]);
      }
      Serial.println("______________________________________");
      int tile_index = 0;
      while (Check_Nearby_Visited(Unvisited[tile_index], Unvisited[tile_index + 1]) == 0)
      {
        tile_index += 2;
      }
      Serial.print(Unvisited[tile_index]);
      Serial.print(",");
      Serial.println(Unvisited[tile_index + 1]);
      Serial.print(X_Position);
      Serial.print(",");
      Serial.println(Y_Position);

      if (Generate_Naive_Path_XY(X_Position, Y_Position, Unvisited[tile_index], Unvisited[tile_index + 1]))
      {
        int Start_X = X_Position;
        int Start_Y = Y_Position;
        int End_X = Unvisited[tile_index];
        int End_Y = Unvisited[tile_index + 1];
        if (End_X < Start_X)
        {
          int X_Direction = 3 - Direction;
          switch (X_Direction)
          {
            case 2:
              Serial.println("go 2 left 1");
              Move('L', 0, turn_angle_L);
              Move('L', 0, turn_angle_L);
              break;
            case 1:
              Serial.println("go 1 right 1");
              Move('R', 0, turn_angle_R);
              break;
            case 3:
              Serial.println("go 1 left 2");
              Move('L', 0, turn_angle_L);
              break;
            case 0:
              Serial.println("as you are 1");
              break;
          }

          for (int i = 0; i < abs(End_X - Start_X); i++)
            Move('Y', 2330, 0);

          if (End_Y < Start_Y)
          {

            int Y_Direction = 2 - Direction;
            switch (Y_Direction)
            {
              case 2:
                Serial.println("go 2 left 3");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 4");
                Move('L', 0, turn_angle_L);
                break;
              case 1:
                Serial.println("go 1 right 5");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as yo are 2");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }

          else if(End_Y > Start_Y)
          {
            int Y_Direction = 0 - Direction;
            switch (Y_Direction)
            {
              case -2:
                Serial.println("go 2 left 6");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 7");
                Move('L', 0, turn_angle_L);
                break;
              case -3:
                Serial.println("go 1 right 8");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as yo are 3");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }
        }

        else if(End_X > Start_X)
        {
          int X_Direction = 1 - Direction;
          switch (X_Direction)
          {
            case -2:
              Serial.println("go 2 left 9");
              Move('L', 0, turn_angle_L);
              Move('L', 0, turn_angle_L);
              break;
            case -1:
              Serial.println("go 1 left 10");
              Move('L', 0, turn_angle_L);
              break;
            case 1:
              Serial.println("go 1 right 11");
              Move('R', 0, turn_angle_R);
              break;
            case 0:
              Serial.println("as you are 4");
              break;
          }
          for (int i = 0; i < abs(End_X - Start_X); i++)
            Move('Y', 2330, 0);
          if (End_Y < Start_Y)
          {

            int Y_Direction = 2 - Direction;
            switch (Y_Direction)
            {
              case 2:
                Serial.println("go 2 left 12");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 13");
                Move('L', 0, turn_angle_L);
                break;
              case 1:
                Serial.println("go 1 right 14");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 5");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }

          else if(End_Y > Start_Y)
          {
            int Y_Direction = 0 - Direction;
            switch (Y_Direction)
            {
              case -2:
                Serial.println("go 2 left 15");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 16");
                Move('L', 0, turn_angle_L);
                break;
              case -3:
                Serial.println("go 1 right 17");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 6");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }
        }

        else if(End_X == Start_X)
        {
          if (End_Y < Start_Y)
          {

            int Y_Direction = 2 - Direction;
            switch (Y_Direction)
            {
              case 2:
                Serial.println("go 2 left 12");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 13");
                Move('L', 0, turn_angle_L);
                break;
              case 1:
                Serial.println("go 1 right 14");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 5");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }

          else if(End_Y > Start_Y)
          {
            int Y_Direction = 0 - Direction;
            switch (Y_Direction)
            {
              case -2:
                Serial.println("go 2 left 15");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 16");
                Move('L', 0, turn_angle_L);
                break;
              case -3:
                Serial.println("go 1 right 17");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 6");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }
        }
      }
      else
      {
        if (Generate_Naive_Path_YX(X_Position, Y_Position, Unvisited[tile_index], Unvisited[tile_index + 1]))
        {
          int Start_X = X_Position;
          int Start_Y = Y_Position;
          int End_X = Unvisited[tile_index];
          int End_Y = Unvisited[tile_index + 1];
          if (End_Y  < Start_Y)
          {
            int Y_Direction = 2 - Direction;
            switch (Y_Direction)
            {
              case 2:
                Serial.println("go 2 left 18");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 19");
                Move('L', 0, turn_angle_L);
                break;
              case 1:
                Serial.println("go 1 right 20");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 7");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
            if (End_X < Start_X)
            {
              int X_Direction = 3 - Direction;
              switch (X_Direction)
              {
                case 2:
                  Serial.println("go 2 left 21");
                  Move('L', 0, turn_angle_L);
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 22");
                  Move('R', 0, turn_angle_R);
                  break;
                case 3:
                  Serial.println("go 1 left 23");
                  Move('L', 0, turn_angle_L);
                  break;
                case 0:
                  Serial.println("as yoi are 8");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }

            else if(End_X > Start_X)
            {
              int X_Direction = 1 - Direction;
              switch (X_Direction)
              {
                case -2:
                  Serial.println("go 2 left 24");
                  Move('L', 0, turn_angle_L);
                  Move('L', 0, turn_angle_L);
                  break;
                case -1:
                  Serial.println("go 1 left 25");
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 26");
                  Move('R', 0, turn_angle_R);
                  break;
                case 0:
                  Serial.println("as you are 9");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }
          }

          else if(End_Y > Start_Y)
          {

            int Y_Direction = 0 - Direction;
            switch (Y_Direction)
            {
              case -2:
                Serial.println("go 2 left 27");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 28");
                Move('L', 0, turn_angle_L);
                break;
              case -3:
                Serial.println("go 1 right 29");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 10");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
            if (End_X < Start_X)
            {
              int X_Direction = 3 - Direction;
              switch (X_Direction)
              {
                case 2:
                  Serial.println("go 2 left 30");
                  Move('L', 0, turn_angle_L);
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 31");
                  Move('R', 0, turn_angle_R);
                  break;
                case 3:
                  Serial.println("go 1 left 32");
                  Move('L', 0, turn_angle_L);
                  break;
                case 0:
                  Serial.println("as you are 11");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }

            else if(End_X > Start_X)
            {
              int X_Direction = 1 - Direction;
              switch (X_Direction)
              {
                case -2:
                  Serial.println("go 2 right 33");
                  Move('R', 0, turn_angle_R);
                  Move('R', 0, turn_angle_R);
                  break;
                case -1:
                  Serial.println("go 1 left 34");
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 35");
                  Move('R', 0, turn_angle_R);
                  break;
                case 0:
                  Serial.println("as you are 12");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }
          }

          else if(End_Y == Start_Y)
          {
            if (End_X < Start_X)
            {
              int X_Direction = 3 - Direction;
              switch (X_Direction)
              {
                case 2:
                  Serial.println("go 2 left 30");
                  Move('L', 0, turn_angle_L);
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 31");
                  Move('R', 0, turn_angle_R);
                  break;
                case 3:
                  Serial.println("go 1 left 32");
                  Move('L', 0, turn_angle_L);
                  break;
                case 0:
                  Serial.println("as you are 11");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }

            else if(End_X > Start_X)
            {
              int X_Direction = 1 - Direction;
              switch (X_Direction)
              {
                case -2:
                  Serial.println("go 2 right 33");
                  Move('R', 0, turn_angle_R);
                  Move('R', 0, turn_angle_R);
                  break;
                case -1:
                  Serial.println("go 1 left 34");
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 35");
                  Move('R', 0, turn_angle_R);
                  break;
                case 0:
                  Serial.println("as you are 12");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }
          }
        }
        else {
          if (TOF_R > 200 && digitalRead(wall_detector_right) == 1) { // if there isn't a wall to your right, turn right then move forward for one tile// && digitalRead(wall_detector_right) == 1
            Move('R', 0, turn_angle_R);
            Move('X', 2600, 0);
          }
          else if (TOF_C < 100) { // if there is a wall in front of you, turn left
            Move('L', 0, turn_angle_L);
          }
          else { // if the there is a wall to your right and there is no wall in front of you, move forward
            Move('F', 2500, 0);
          }
          //          Start_X = X_Position;
          //          Start_Y = Y_Position;
        }
      }

      for (int i = Minimum_X; i <= Maximum_X; i++)
      {
        for (int j = Minimum_Y; j <= Maximum_Y; j++)
        {
          Serial.print(Maze[i][j][4]);
          Serial.print(",(");
          Serial.print(i);
          Serial.print(",");
          Serial.print(j);
          Serial.print(")");
          Serial.print("\t");
        }
        Serial.println("###########################");
      }
    }

    while (X_Position != 20 || Y_Position != 20) {
      Serial.println("Returning Home");
      if (Generate_Naive_Path_XY(X_Position, Y_Position, 20, 20))
      {
        Serial.println("XY Path Back Found");
        int Start_X = X_Position;
        int Start_Y = Y_Position;
        int End_X = 20;
        int End_Y = 20;
        if (End_X < Start_X)
        {
          int X_Direction = 3 - Direction;
          switch (X_Direction)
          {
            case 2:
              Serial.println("go 2 left 1");
              Move('L', 0, turn_angle_L);
              Move('L', 0, turn_angle_L);
              break;
            case 1:
              Serial.println("go 1 right 1");
              Move('R', 0, turn_angle_R);
              break;
            case 3:
              Serial.println("go 1 left 2");
              Move('L', 0, turn_angle_L);
              break;
            case 0:
              Serial.println("as you are 1");
              break;
          }

          for (int i = 0; i < abs(End_X - Start_X); i++)
            Move('Y', 2330, 0);

          if (End_Y < Start_Y)
          {

            int Y_Direction = 2 - Direction;
            switch (Y_Direction)
            {
              case 2:
                Serial.println("go 2 left 3");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 4");
                Move('L', 0, turn_angle_L);
                break;
              case 1:
                Serial.println("go 1 right 5");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as yo are 2");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }

          else if(End_Y > Start_Y)
          {
            int Y_Direction = 0 - Direction;
            switch (Y_Direction)
            {
              case -2:
                Serial.println("go 2 left 6");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 7");
                Move('L', 0, turn_angle_L);
                break;
              case -3:
                Serial.println("go 1 right 8");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as yo are 3");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }
        }

        else if(End_X > Start_X)
        {
          int X_Direction = 1 - Direction;
          switch (X_Direction)
          {
            case -2:
              Serial.println("go 2 left 9");
              Move('L', 0, turn_angle_L);
              Move('L', 0, turn_angle_L);
              break;
            case -1:
              Serial.println("go 1 left 10");
              Move('L', 0, turn_angle_L);
              break;
            case 1:
              Serial.println("go 1 right 11");
              Move('R', 0, turn_angle_R);
              break;
            case 0:
              Serial.println("as you are 4");
              break;
          }
          for (int i = 0; i < abs(End_X - Start_X); i++)
            Move('Y', 2330, 0);
          if (End_Y < Start_Y)
          {

            int Y_Direction = 2 - Direction;
            switch (Y_Direction)
            {
              case 2:
                Serial.println("go 2 left 12");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 13");
                Move('L', 0, turn_angle_L);
                break;
              case 1:
                Serial.println("go 1 right 14");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 5");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }

          else if(End_Y > Start_Y)
          {
            int Y_Direction = 0 - Direction;
            switch (Y_Direction)
            {
              case -2:
                Serial.println("go 2 left 15");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 16");
                Move('L', 0, turn_angle_L);
                break;
              case -3:
                Serial.println("go 1 right 17");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 6");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }
        }

        else if(End_X == Start_X)
        {
          if (End_Y < Start_Y)
          {

            int Y_Direction = 2 - Direction;
            switch (Y_Direction)
            {
              case 2:
                Serial.println("go 2 left 12");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 13");
                Move('L', 0, turn_angle_L);
                break;
              case 1:
                Serial.println("go 1 right 14");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 5");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }

          else if(End_Y > Start_Y)
          {
            int Y_Direction = 0 - Direction;
            switch (Y_Direction)
            {
              case -2:
                Serial.println("go 2 left 15");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 16");
                Move('L', 0, turn_angle_L);
                break;
              case -3:
                Serial.println("go 1 right 17");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 6");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
          }
        }
      }
      else
      {
        if (Generate_Naive_Path_YX(X_Position, Y_Position, 20, 20))
        {
          Serial.println("YX Path Back Found");
          int Start_X = X_Position;
          int Start_Y = Y_Position;
          int End_X = 20;
          int End_Y = 20;
          if (End_Y  < Start_Y)
          {
            int Y_Direction = 2 - Direction;
            switch (Y_Direction)
            {
              case 2:
                Serial.println("go 2 left 18");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 19");
                Move('L', 0, turn_angle_L);
                break;
              case 1:
                Serial.println("go 1 right 20");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 7");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
            if (End_X < Start_X)
            {
              int X_Direction = 3 - Direction;
              switch (X_Direction)
              {
                case 2:
                  Serial.println("go 2 left 21");
                  Move('L', 0, turn_angle_L);
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 22");
                  Move('R', 0, turn_angle_R);
                  break;
                case 3:
                  Serial.println("go 1 left 23");
                  Move('L', 0, turn_angle_L);
                  break;
                case 0:
                  Serial.println("as yoi are 8");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }

            else if(End_X > Start_X)
            {
              int X_Direction = 1 - Direction;
              switch (X_Direction)
              {
                case -2:
                  Serial.println("go 2 left 24");
                  Move('L', 0, turn_angle_L);
                  Move('L', 0, turn_angle_L);
                  break;
                case -1:
                  Serial.println("go 1 left 25");
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 26");
                  Move('R', 0, turn_angle_R);
                  break;
                case 0:
                  Serial.println("as you are 9");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }
          }

          else if(End_Y > Start_Y)
          {

            int Y_Direction = 0 - Direction;
            switch (Y_Direction)
            {
              case -2:
                Serial.println("go 2 left 27");
                Move('L', 0, turn_angle_L);
                Move('L', 0, turn_angle_L);
                break;
              case -1:
                Serial.println("go 1 left 28");
                Move('L', 0, turn_angle_L);
                break;
              case -3:
                Serial.println("go 1 right 29");
                Move('R', 0, turn_angle_R);
                break;
              case 0:
                Serial.println("as you are 10");
                break;
            }
            for (int i = 0; i < abs(End_Y - Start_Y); i++)
              Move('Y', 2330, 0);
            if (End_X < Start_X)
            {
              int X_Direction = 3 - Direction;
              switch (X_Direction)
              {
                case 2:
                  Serial.println("go 2 left 30");
                  Move('L', 0, turn_angle_L);
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 31");
                  Move('R', 0, turn_angle_R);
                  break;
                case 3:
                  Serial.println("go 1 left 32");
                  Move('L', 0, turn_angle_L);
                  break;
                case 0:
                  Serial.println("as you are 11");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }

            else if(End_X > Start_X)
            {
              int X_Direction = 1 - Direction;
              switch (X_Direction)
              {
                case -2:
                  Serial.println("go 2 right 33");
                  Move('R', 0, turn_angle_R);
                  Move('R', 0, turn_angle_R);
                  break;
                case -1:
                  Serial.println("go 1 left 34");
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 35");
                  Move('R', 0, turn_angle_R);
                  break;
                case 0:
                  Serial.println("as you are 12");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }
          }

          else if(End_Y == Start_Y)
          {
            if (End_X < Start_X)
            {
              int X_Direction = 3 - Direction;
              switch (X_Direction)
              {
                case 2:
                  Serial.println("go 2 left 30");
                  Move('L', 0, turn_angle_L);
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 31");
                  Move('R', 0, turn_angle_R);
                  break;
                case 3:
                  Serial.println("go 1 left 32");
                  Move('L', 0, turn_angle_L);
                  break;
                case 0:
                  Serial.println("as you are 11");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }

            else if(End_X > Start_X)
            {
              int X_Direction = 1 - Direction;
              switch (X_Direction)
              {
                case -2:
                  Serial.println("go 2 right 33");
                  Move('R', 0, turn_angle_R);
                  Move('R', 0, turn_angle_R);
                  break;
                case -1:
                  Serial.println("go 1 left 34");
                  Move('L', 0, turn_angle_L);
                  break;
                case 1:
                  Serial.println("go 1 right 35");
                  Move('R', 0, turn_angle_R);
                  break;
                case 0:
                  Serial.println("as you are 12");
                  break;
              }
              for (int i = 0; i < abs(End_X - Start_X); i++)
                Move('Y', 2330, 0);
            }
          }
        }
        else {
          Serial.println("offffffff");
          //&& digitalRead(wall_detector_right) == 1
          if (TOF_R > 200) { // if there isn't a wall to your right, turn right then move forward for one tile// && digitalRead(wall_detector_right) == 1
            Move('R', 0, turn_angle_R);
            Move('X', 2600, 0);
          }
          else if (TOF_C < 100) { // if there is a wall in front of you, turn left
            Move('L', 0, turn_angle_L);
          }
          else { // if the there is a wall to your right and there is no wall in front of you, move forward
            Move('F', 2500, 0);
          }
          //          Start_X = X_Position;
          //          Start_Y = Y_Position;
        }
      }

      for (int i = Minimum_X; i <= Maximum_X; i++)
      {
        for (int j = Minimum_Y; j <= Maximum_Y; j++)
        {
          Serial.print(Maze[i][j][4]);
          Serial.print(",(");
          Serial.print(i);
          Serial.print(",");
          Serial.print(j);
          Serial.print(")");
          Serial.print("\t");
        }
        Serial.println("###########################");
      }
    }

    /*for(int i = Minimum_X; i <= Maximum_X; i++)
      {
      for(int j = Minimum_Y; j <= Maximum_Y; j++)
      {
        Serial.print(Maze[i][j][0]);
        Serial.print(",(");
        Serial.print(i);
        Serial.print(",");
        Serial.print(j);
        Serial.print(")");
        Serial.print("\t");
      }
      Serial.println("###########################");
      }

      for(int i = Minimum_X; i <= Maximum_X; i++)
      {
      for(int j = Minimum_Y; j <= Maximum_Y; j++)
      {
        Serial.print(Maze[i][j][1]);
        Serial.print(",(");
        Serial.print(i);
        Serial.print(",");
        Serial.print(j);
        Serial.print(")");
        Serial.print("\t");
      }
      Serial.println("###########################");
      }

      for(int i = Minimum_X; i <= Maximum_X; i++)
      {
      for(int j = Minimum_Y; j <= Maximum_Y; j++)
      {
        Serial.print(Maze[i][j][2]);
        Serial.print(",(");
        Serial.print(i);
        Serial.print(",");
        Serial.print(j);
        Serial.print(")");
        Serial.print("\t");
      }
      Serial.println("###########################");
      }

      for(int i = Minimum_X; i <= Maximum_X; i++)
      {
      for(int j = Minimum_Y; j <= Maximum_Y; j++)
      {
        Serial.print(Maze[i][j][3]);
        Serial.print(",(");
        Serial.print(i);
        Serial.print(",");
        Serial.print(j);
        Serial.print(")");
        Serial.print("\t");
      }
      Serial.println("###########################");
      }*/
    while (1)
    {
      MoveWheels(LOW, 0, LOW, 0, "Stop");
    }
  }
  else
  {
    Start_Tile = 0;
    if (TOF_R > 200 && digitalRead(wall_detector_right) == 1) { // if there isn't a wall to your right, turn right then move forward for one tile// && digitalRead(wall_detector_right) == 1
      Move('R', 0, turn_angle_R);
      Move('X', 2600, 0);
    }
    else if (TOF_C < 100) { // if there is a wall in front of you, turn left
      Move('L', 0, turn_angle_L);
    }
    else { // if the there is a wall to your right and there is no wall in front of you, move forward
      Move('F', 2500, 0);
    }
  }
}
