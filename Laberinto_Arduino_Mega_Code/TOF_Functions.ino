void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
  //delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, HIGH);
  digitalWrite(SHT_LOX5, HIGH);
  //delay(10);

  // activating LOX1 and reseting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);

  // initing LOX1
  if (!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1);
  }
  //delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  //delay(10);

  //initing LOX2
  if (!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1);
  }

  // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  //delay(10);

  //initing LOX3
  if (!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while (1);
  }

  // activating LOX4
  digitalWrite(SHT_LOX4, HIGH);
  //delay(10);

  //initing LOX4
  if (!lox4.begin(LOX4_ADDRESS)) {
    Serial.println(F("Failed to boot fourth VL53L0X"));
    while (1);
  }

  // activating LOX5
  digitalWrite(SHT_LOX5, HIGH);
  //delay(10);

  //initing LOX5
  if (!lox5.begin(LOX5_ADDRESS)) {
    Serial.println(F("Failed to boot fifth VL53L0X"));
    while (1);
  }


}

void read_all_TOFs() {

  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!
  lox4.rangingTest(&measure4, false); // pass in 'true' to get debug data printout!
  lox5.rangingTest(&measure5, false); // pass in 'true' to get debug data printout!

  //1--> right
  //2--> left
  //3--> F_Right
  //4--> F_Left
  //5--> right_F

  TOF_R = measure1.RangeMilliMeter;
  TOF_L = measure2.RangeMilliMeter;
  TOF_C_R = measure3.RangeMilliMeter;
  TOF_C_L = measure4.RangeMilliMeter;
  TOF_R_F = measure5.RangeMilliMeter;

  /*************New Regression**************/
  TOF_C_L = 0.963013751 * TOF_C_L - 15.83158222;
  TOF_C_R = 0.938806605 * TOF_C_R + 5.877418983;
  TOF_R_F = 1.004724431 * TOF_R_F - 19.24644261;    //remove sticker and recalculate regression
  TOF_R = 0.957286559 * TOF_R - 0.378658536;
  /*************END of New Regression**************/

  

  /*************Printing TOF Values**************/
  Serial.print("TOF_L = ");
  Serial.print(TOF_L);
  Serial.print("\tTOF_C_L = ");
  Serial.print(TOF_C_L);
  Serial.print("\tTOF_C_R = ");
  Serial.print(TOF_C_R);
  Serial.print("\tTOF_R = ");
  Serial.print(TOF_R);
  Serial.print("\tTOF_R_F = ");
  Serial.print(TOF_R_F);
  Serial.print("\t");
  /*************END of Printing TOF Values**************/

//  Serial.print("TOF_R: ");
//  Serial.print(TOF_R);
////  Serial.print("\tTOF_C_R: ");
////  Serial.print(TOF_C_R);
////  Serial.print("\tTOF_C_L: ");
////  Serial.print(TOF_C_L);
//  Serial.print("\tTOF_L: ");
//  Serial.print(TOF_L);
}
