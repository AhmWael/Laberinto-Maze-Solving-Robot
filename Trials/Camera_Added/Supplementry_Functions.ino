void deploy_kit (char posik, int kits) {
  if (posik == 'r') {
    digitalWrite(buzzer, HIGH);
    MoveWheels(LOW, 0, LOW, 0, "Stop");
    timer = millis();
    while ((kits > 0) || (millis() - timer <= 5000)) {
      if (kits > 0) {
        myservo.write(145);
        delay(20);
        for (int pos = 130; pos >= 53; pos --) {//right
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
