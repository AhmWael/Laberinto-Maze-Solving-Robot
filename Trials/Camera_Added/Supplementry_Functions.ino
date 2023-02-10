void deploy_kit (char posik, int kits) {
  if (posik == 'r') {
    digitalWrite(buzzer, HIGH);
    MoveWheels(LOW, 0, LOW, 0, "Stop");
    timer = millis();
    while ((kits > 0) || (millis() - timer <= 5000)) {
      if (kits > 0) {
        //        myservo.write(-5);
        for (int pos = 62; pos <= 145; pos += 1) {//right
          myservo.write(pos);
          delay(15);
        }
        //        for (int pos = 55; pos >= -5; pos -= 1) { //left
        //          myservo.write(pos);
        //          delay(15);
        //        }
        myservo.write(62); // neutral
        delay(30);
        kits --;
      }
    }
    //delay(4000);
    digitalWrite(buzzer, LOW);
  }

  else if (posik == 'l') {
    digitalWrite(buzzer, HIGH);
  }
}
