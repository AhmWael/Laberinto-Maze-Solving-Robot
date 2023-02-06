#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;
int signal1 = 11 ;
int signal2 = 12 ;

void setup() {
  Serial.begin(115200);
  pinMode (signal1,OUTPUT);
  pinMode (signal2,OUTPUT);

  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);
}

void loop() {
  //create some variables to store the color data in
  uint16_t r, g, b, c;
  
  //wait for color data to be ready
  while(!apds.colorDataReady()){
    delay(5);
  }

  //get the data and print the different channels
  apds.getColorData(&r, &g, &b, &c);
  Serial.print("red: ");
  Serial.print(r);
  
  Serial.print(" green: ");
  Serial.print(g);
  
  Serial.print(" blue: ");
  Serial.print(b);
  
  Serial.print(" clear: ");
  Serial.println(c);
  Serial.println();

  if((r<40) && (g<40) && (b<40))
  {
    Serial.println(" BLACK Detected: ");
    digitalWrite(signal1,HIGH);
    digitalWrite(signal2,HIGH);
  }

  else if((b-r >= 90) && (b-g >= 90) && (b > 150))
  {
    Serial.println(" BLUE Detected: ");
    digitalWrite(signal1,LOW);
    digitalWrite(signal2,HIGH);
  }

  else if((r>350) && (g>350) && (b>350))
  {
    Serial.println(" WHITE Detected: ");
    digitalWrite(signal1,LOW);
    digitalWrite(signal2,LOW);
  }
  
//  delay(500);
//  int red = digitalRead(r);
//  int blue = digitalRead(b);
//  int green = digitalRead(g);
 

  
//  if (r>b&&r>g){
//    digitalWrite(signal1,HIGH);
//    digitalWrite(signal2,LOW);
//    delay(5000);
//    digitalWrite(signal1,LOW);
//  }
// else if (g>r&&g>b){
//     digitalWrite(signal2,HIGH);
//     digitalWrite(signal1,LOW);
//     delay(5000);
//     digitalWrite(signal2,LOW);
//     
//  }
//  else {
//    digitalWrite(signal2,LOW);
//    digitalWrite(signal1,LOW);
//  }
  
  }
