void Solve() {
  read_all_TOFs();
  /* for testing TOF
//  Serial.print("TOF_C:");
//  Serial.print(TOF_C);
//  Serial.print("\tTOF_R:");
//  Serial.println(TOF_R);
*/
  
  if (TOF_R > 200) { // if there isn't a wall to your right, turn right then move forward for one tile
    Move('R');
    Move('F');
  }
  else if (TOF_C < 100) { // if there is a wall in front of you, turn left
    Move('L');
  }
  else { // if the there is a wall to your right and there is no wall in front of you, move forward
    Move('F');
  }
}
