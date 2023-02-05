//Repeat(){
//  
//}

void Victim_Found (char pos){
  if(pos == 'r')
  {
    digitalWrite(buzzer, HIGH);
    timer = millis();
    
    while (millis() - timer <= 4000) {
      read_all_TOFs();
      digitalWrite(buzzer, HIGH);
      MoveWheels(HIGH, 0, HIGH, 0, "Stop");
    }
    digitalWrite(buzzer, LOW);
    
  }
  else if(pos == 'l')
  {
    digitalWrite(buzzer, HIGH);
  }
  servo.write(180);
  
}
