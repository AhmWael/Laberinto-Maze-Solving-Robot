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
    MoveWheels(LOW, 0, HIGH, 0, "Stop");
  }
}

bool isBlack (){
  Col_1 = digitalRead(Col_1_pin);
  Col_2 = digitalRead(Col_2_pin);

  if (Col_1 == 1 && Col_2 == 1 && tilt_f != 1 && tilt_b != 1) {
    Serial.println(" Color Serial --> Black Floor Found ");
    //MoveWheels(LOW, 0, HIGH, 0, "Stop");
    return true;
  }
  else {
    return false;
  }
}

bool isBlue(){
  Col_1 = digitalRead(Col_1_pin);
  Col_2 = digitalRead(Col_2_pin);

  if (Col_1 == 0 && Col_2 == 1 && tilt_f != 1 && tilt_b != 1) {
    Serial.println(" Color Serial --> Blue Floor Found ");
    return true;
  }
  else{
    return false;
  }
}
