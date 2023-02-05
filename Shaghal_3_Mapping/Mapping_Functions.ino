void initialise_the_map() {
  for (int x = 0; x < 60; x ++) {
    for (int y = 0; y < 60; y ++) {
      if ((x % 2 == 1) && (y % 2 == 1)) {
        maze[x][y] = 'X';
      }
      else if ((x % 2 == 0) && (y % 2 == 0)) {
        maze[x][y] = 'N';
      }
      else {
        maze[x][y] = '?';
      }
    }
  }
}

bool isValidWalls (int x, int y) {
  if ((x >= 0) && (x < 60) && (y >= 0) && (y < 60))
    return 1;
  else 
    return 0;
}

bool isRW() {
  if (robot_dir == 0) {
    if (isValidWalls(x_maze + 1, y_maze) && (maze[x_maze + 1][y_maze] == '#')) {
      return 1;
    }
  }

  if (robot_dir == 1) {
    if (isValidWalls(x_maze, y_maze - 1) && (maze[x_maze][y_maze - 1] == '#')) {
      return 1;
    }
  }
  
  if (robot_dir == 2) {
    if (isValidWalls(x_maze - 1, y_maze) && (maze[x_maze - 1][y_maze] == '#')) {
      return 1;
    }
  }

  if (robot_dir == 3) {
    if (isValidWalls(x_maze, y_maze + 1) && (maze[x_maze][y_maze + 1] == '#')) {
      return 1;
    }
  }

  return 0;
}

bool isFW() {
  if (robot_dir == 0) {
    if (isValidWalls(x_maze, y_maze + 1) && (maze[x_maze][y_maze + 1] == '#')) {
      return 1;
    }
  }

  if (robot_dir == 1) {
    if (isValidWalls(x_maze + 1, y_maze) && (maze[x_maze + 1][y_maze] == '#')) {
      return 1;
    }
  }
  
  if (robot_dir == 2) {
    if (isValidWalls(x_maze, y_maze - 1) && (maze[x_maze][y_maze - 1] == '#')) {
      return 1;
    }
  }

  if (robot_dir == 3) {
    if (isValidWalls(x_maze - 1, y_maze) && (maze[x_maze - 1][y_maze] == '#')) {
      return 1;
    }
  }

  return 0;
}

void search_for_walls() {
  read_all_TOFs();
  bool fw = 0, lw = 0, rw = 0;
  if (TOF_C <= 140)
    fw = 1;
  if (TOF_L <= 200)
    lw = 1;
  if (TOF_R <= 200)
    rw = 1;

  if (robot_dir == 0) {
    if (isValidWalls(x_maze, y_maze + 1) && (fw)) {
      maze[x_maze][y_maze + 1] = '#';
    }
    else {
      maze[x_maze][y_maze + 1] = ' ';
    }
    if (isValidWalls(x_maze + 1, y_maze) && (rw)) {
      maze[x_maze + 1][y_maze] = '#';
    }
    else {
      maze[x_maze + 1][y_maze] = ' ';
    }
    if (isValidWalls(x_maze - 1, y_maze) && (lw)) {
      maze[x_maze - 1][y_maze] = '#';
    }
    else {
      maze[x_maze - 1][y_maze] = ' ';
    }
  }

  if (robot_dir == 1) {
    if (isValidWalls(x_maze, y_maze + 1) && (lw)) {
      maze[x_maze][y_maze + 1] = '#';
    }
    else {
      maze[x_maze][y_maze + 1] = ' ';
    }
    if (isValidWalls(x_maze + 1, y_maze) && (fw)) {
      maze[x_maze + 1][y_maze] = '#';
    }
    else {
      maze[x_maze + 1][y_maze] = ' ';
    }
    if (isValidWalls(x_maze, y_maze - 1) && (rw)) {
      maze[x_maze][y_maze - 1] = '#';
    }
    else {
      maze[x_maze][y_maze - 1] = ' ';
    }
  }
  
  if (robot_dir == 2) {
    if (isValidWalls(x_maze, y_maze - 1) && (fw)) {
      maze[x_maze][y_maze - 1] = '#';
    }
    else {
      maze[x_maze][y_maze - 1] = ' ';
    }
    if (isValidWalls(x_maze + 1, y_maze) && (lw)) {
      maze[x_maze + 1][y_maze] = '#';
    }
    else {
      maze[x_maze + 1][y_maze] = ' ';
    }
    if (isValidWalls(x_maze - 1, y_maze) && (rw)) {
      maze[x_maze - 1][y_maze] = '#';
    }
    else {
      maze[x_maze - 1][y_maze] = ' ';
    }
  }

  if (robot_dir == 3) {
    if (isValidWalls(x_maze, y_maze + 1) && (rw)) {
      maze[x_maze][y_maze + 1] = '#';
    }
    else {
      maze[x_maze][y_maze + 1] = ' ';
    }
    if (isValidWalls(x_maze - 1, y_maze) && (fw)) {
      maze[x_maze - 1][y_maze] = '#';
    }
    else {
      maze[x_maze - 1][y_maze] = ' ';
    }
    if (isValidWalls(x_maze, y_maze - 1) && (lw)) {
      maze[x_maze][y_maze - 1] = '#';
    }
    else {
      maze[x_maze][y_maze - 1] = ' ';
    }
  }
}
