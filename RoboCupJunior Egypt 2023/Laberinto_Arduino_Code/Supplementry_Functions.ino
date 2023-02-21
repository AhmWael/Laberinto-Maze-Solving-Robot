void deploy_kit (char posik, int kits) {
  if (posik == 'r') {
    //    digitalWrite(buzzer, HIGH);
    MoveWheels(LOW, 0, LOW, 0, "Stop");
    int time_interval = 0;
    timer = millis();
    while ((kits > 0) || (millis() - timer <= 5000)) {
      //      if (millis() - 500 * time_interval >= 500)
      //        time_interval ++;
      if (millis() - timer <= 1000)
        digitalWrite(buzzer, HIGH);
      else if (millis() - timer <= 2000)
        digitalWrite(buzzer, LOW);
      else if (millis() - timer <= 3000)
        digitalWrite(buzzer, HIGH);
      else if (millis() - timer <= 4000)
        digitalWrite(buzzer, LOW);
      else if (millis() - timer <= 5000)
        digitalWrite(buzzer, HIGH);
      if (kits > 0) {
        for (int pos = 52; pos <= 150; pos += 4) {//right
          myservo.write(pos);
          delay(12);
        }
        delay(20);
        for (int pos = 150; pos >= 52; pos -= 2) {//right
          myservo.write(pos);
          delay(15);
        }
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
