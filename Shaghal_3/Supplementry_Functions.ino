//Repeat(){
//  
//}

void Victim_Found (char pos){
  if(pos == 'r')
  {
    digitalWrite(buzzer, HIGH);
    
  }
  else if(pos == 'l')
  {
    digitalWrite(buzzer, HIGH);
  }
  myservo.write(pos);
  
}
