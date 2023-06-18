void Add_Tile() {
  // This function adds the necessary information for each tile in the 3D Array named Maze
  // X_Position and Y_Position are changed according to the direction
  if (Direction == 0)
    Y_Position++;
  else if (Direction == 1)
    X_Position++;
  else if (Direction == 2)
    Y_Position--;
  else
    X_Position--;
  Maze[X_Position][Y_Position][4] = 1;
  read_all_TOFs();
  Minimum_X = min(Minimum_X, X_Position);
  Minimum_Y = min(Minimum_Y, Y_Position);
  Maximum_X = max(Maximum_X, X_Position);
  Maximum_Y = max(Maximum_Y, Y_Position);
  if (TOF_L < 200)
    Maze[X_Position][Y_Position][(Direction + 3) % 4] = 1;
  if (((TOF_C_L + TOF_C_R) / 2) < 150)
    Maze[X_Position][Y_Position][Direction] = 1;
  if (((TOF_R_F + TOF_R) / 2) < 200)
    Maze[X_Position][Y_Position][(Direction + 1) % 4] = 1;
}


void Change_Direction(char Turn) {
  if (Turn == 'L')
    Direction = (Direction + 3) % 4; // 90 degrees to the left
  else
    Direction = (Direction + 1) % 4; // 90 degrees to the right

}

int Size() {
  // This function returns number of unvisited tiles
  int counter = 0;
  for (int i = Minimum_X; i <= Maximum_X; i++)
  {
    for (int j = Minimum_Y; j <= Maximum_Y; j++)
    {
      if (Maze[i][j][4] == 0)
        counter++;
    }
  }
  return counter;
}

void Generate_unvisited_array()
{
  // This function saves the positions of the unvisited tiles in the array Unvisited
  // the array will look like this [x1, y1, x2, y2, ...........]
  // where x1 is the x-coordinate of the first unvisited tile and y1 y-coordinate of the first unvisited tile and so on
  // the size of this array will 2 * Size()
  int index = 0;
  for (int i = Minimum_X; i <= Maximum_X; i++)
  {
    for (int j = Minimum_Y; j <= Maximum_Y; j++)
    {
      if (Maze[i][j][4] == 0)
      {
        Unvisited[index] = i;
        index++;
        Unvisited[index] = j;
        index++;
      }
    }
  }
}

double Distance(int x1, int y1, int x2, int y2) {
  // This function calculates the distance from given position to required position
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
void swap(int *xp, int *yp) {
  // This function swaps the first parameter with the second one
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void Sort_Unvisited(int n) {
  
  int i, j, min_idx, min_idx_y;
  for (i = 0; i < n - 2; i += 2)
  {
    // Find the minimum element in
    // unsorted array
    min_idx = i;
    min_idx_y = i + 1;
    double Minimum_Distance = Distance(X_Position, Y_Position, Unvisited[i], Unvisited[i + 1]);
    for (j = i + 2; j < n; j += 2)
    {
      if (Distance(X_Position, Y_Position, Unvisited[j], Unvisited[j + 1]) < Minimum_Distance)
      {
        min_idx = j;
        min_idx_y = j + 1;
        Minimum_Distance = Distance(X_Position, Y_Position, Unvisited[j], Unvisited[j + 1]);
      }
    }
    // Swap the found minimum element
    // with the first element
    if (min_idx != i)
    {
      swap(&Unvisited[min_idx], &Unvisited[i]);
      swap(&Unvisited[min_idx_y], &Unvisited[i + 1]);
    }
  }
}
int Check_Wall(int x1, int y1, int x2, int y2) {
  // This function checks if there is a wall in the way of getting to a certain point or not
  if (y2 < y1)
    if (Maze[x2][y2][0] == 0)
      return 1;
  if (y2 > y1)
    if (Maze[x2][y2][2] == 0)
      return 1;
  if (x2 < x1)
    if (Maze[x2][y2][1] == 0)
      return 1;
  if (x2 > x1)
    if (Maze[x2][y2][3] == 0)
      return 1;
}

int Check_Nearby_Visited(int x, int y) {
  // This function checks if a function is accessible by checking the neighboring visited tiles and check if there is a wall blocking the path or not
  int flag = 0;
  if (Maze[x + 1][y][4])
    if (Check_Wall(x, y, x + 1, y))
      flag++;

  if (Maze[x - 1][y][4])
    if (Check_Wall(x, y, x - 1, y))
      flag++;

  if (Maze[x][y + 1][4])
    if (Check_Wall(x, y, x, y + 1))
      flag++;

  if (Maze[x][y - 1][4])
    if (Check_Wall(x, y, x, y - 1))
      flag++;
  return flag;
}

bool Generate_Naive_Path_XY(int Start_X, int Start_Y, int End_X, int End_Y) {
  // This function is responsible for checking if the robot can move from a starting tile to destination tile by moving in the x direction first followed by the y direction
  if (End_X < Start_X)
  {
    while (End_X != Start_X)
    {
      if (Maze[Start_X][Start_Y][3] == 1)
        return 0;
      Start_X--;
    }
  }
  else
  {

    while (End_X != Start_X)
    {
      if (Maze[Start_X][Start_Y][1] == 1)
        return 0;
      Start_X++;
    }
  }

  if (End_Y < Start_Y)
  {
    while (End_Y != Start_Y)
    {
      if (Maze[Start_X][Start_Y][2] == 1)
        return 0;
      Start_Y--;
    }
  }
  else
  {

    while (End_Y != Start_Y)
    {
      if (Maze[Start_X][Start_Y][0] == 1)
        return 0;
      Start_Y++;
    }
  }
  return 1;
}

bool Generate_Naive_Path_YX(int Start_X, int Start_Y, int End_X, int End_Y) {
  // This function is responsible for checking if the robot can move from a starting tile to destination tile by moving in the y direction first followed by the x direction
  if (End_Y < Start_Y)
  {
    while (End_Y != Start_Y)
    {
      if (Maze[Start_X][Start_Y][2] == 1)
        return 0;
      Start_Y--;
    }
  }
  else
  {

    while (End_Y != Start_Y)
    {
      if (Maze[Start_X][Start_Y][0] == 1)
        return 0;
      Start_Y++;
    }
  }

  if (End_X < Start_X)
  {
    while (End_X != Start_X)
    {
      if (Maze[Start_X][Start_Y][3] == 1)
        return 0;
      Start_X--;
    }
  }
  else
  {

    while (End_X != Start_X)
    {
      if (Maze[Start_X][Start_Y][1] == 1)
        return 0;
      Start_X++;
    }
  }
  return 1;
}

bool Check_Unvisited_Availability(int sizee) {
  // This function returns 1 if the tile is totally unaccessible
  for (int i = 0; i < sizee; i += 2)
    if (Check_Nearby_Visited(Unvisited[i], Unvisited[i + 1]) != 0)
      return 1;
  return 0;
}
