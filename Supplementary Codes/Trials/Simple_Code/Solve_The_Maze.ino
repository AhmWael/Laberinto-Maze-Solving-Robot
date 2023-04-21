void Solve() {
  read_all_TOFs();
  Serial.print("TOF_C:");
  Serial.print(TOF_C);
  Serial.print("\tTOF_R:");
  Serial.println(TOF_R);
  
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
