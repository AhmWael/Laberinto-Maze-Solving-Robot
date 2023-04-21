 
void read_all_TOFs () {

  if (Serial3.available()) {
    received_dist_3 = Serial3.readStringUntil('\n');
    //Serial.println(received_dist);
    TOF_C = received_dist_3.toInt();
    //Serial.println(TOF_C);
    //    Serial.print("TOF_C : ");
    //    Serial.println(TOF_C);
  }

  if (Serial2.available()) {
    received_dist_2 = Serial2.readStringUntil('\n');
    //Serial.println(received_dist);
    TOF_R = received_dist_2.toInt();
    //Serial.println(TOF_R);
        Serial.print("TOF_R : ");
        Serial.println(TOF_R);
  }

  if (Serial1.available()) {
    received_dist_1 = Serial1.readStringUntil('\n');
    //Serial.println(received_dist);
    //TOF_L = received_dist_1.toInt();
    //Serial.println(TOF_L);
    //    Serial.print("TOF_L : ");
    //    Serial.println(TOF_L);
  }

  //mo2akatan
  TOF_L = 201;
}
