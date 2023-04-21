void read_all_TOFs () {
  if (Serial2.available()) {
    received_dist_2 = Serial2.readStringUntil('\n');
    TOF_R = received_dist_2.toInt();
  }

  if (Serial3.available()) {
    received_dist_3 = Serial3.readStringUntil('\n');
    TOF_C = received_dist_3.toInt();
  }
}
