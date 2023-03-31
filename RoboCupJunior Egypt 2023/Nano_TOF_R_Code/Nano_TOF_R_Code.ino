#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int dist;//max --> 19528
void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test.");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  // power
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  // start continuous ranging
  lox.startRangeContinuous();

}


void loop() {


  if (lox.isRangeComplete()) {
    dist = lox.readRange();
    String dist_str = String(dist);

    if (dist_str.length() == 1) {
      dist_str = "000" + dist_str;
    }
    else if (dist_str.length() == 2) {
      dist_str = "00" + dist_str;
    }
    else if (dist_str.length() == 3) {
      dist_str = "0" + dist_str;
    }
    //else if(dist_str.length() == 4){ dist_str = "" + dist_str; }

    for (int i = 0; i < dist_str.length(); i++)
    {
      Serial.write(dist_str.charAt(i));
    }
    Serial.write('\n');
    delay(3);
    //Serial.println(dist_str);
  }

  //Serial.write(dist);
}
/*
  #include "Adafruit_VL53L0X.h"

  Adafruit_VL53L0X lox = Adafruit_VL53L0X();

  void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test.");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  // start continuous ranging
  lox.startRangeContinuous();
  }

  void loop() {
  if (lox.isRangeComplete()) {
    int dist = lox.readRange();
  //    int dummy = dist, counter = 0;
  //    while (dummy != 0) {
  //      counter ++;
  //      dummy /= 10;
  //    }
  //    dist += (counter * power(10, counter));
    Serial.print("Distance in mm: ");
    Serial.println(dist);
    Serial.write(dist);
  }
  }

  int power(int a, int b)
  {
  int res = 1;
  for(int i = 0; i < b; i++)
  {
    res *= a;
  }
  return res;
  }
*/
