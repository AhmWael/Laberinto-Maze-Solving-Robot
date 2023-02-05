void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}

void readEncoder1(){
  int b = digitalRead(ENCBr);
  if(b > 0){
    posir++;
  }
  else{
    posir--;
  }
}

void readEncoder2(){
  int b = digitalRead(ENCBl);
  if(b > 0){
    posil++;
  }
  else{
    posil--;
  }
}
