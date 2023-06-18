// Importing needed libraries
#include <Wire.h>
#include <Arduino_LSM6DS3.h>
#include <MadgwickAHRS.h>
#include "Adafruit_TCS34725.h"
#include <SPI.h>

Madgwick filter;

//#define DT 0.01 // time step in seconds
#define ALPHA 0.98 // tuning parameter for complementary filter
//#define bias_error 0.1; // Bias error in yaw measurement

float pitch, roll, yaw; // pitch, roll, and yaw angles
//float wz_prev = 0; // previous angular velocity around z-axis
//unsigned long prev_time = 0; // previous time stamp

float ax, ay, az, gx, gy, gz, err_gx, err_gy, err_gz;
int high_pitch_count = 0;

// our RGB -> eye-recognized gamma color
byte gammatable[256];

// Color sensor initialisation
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#define white_button 9
#define blue_button 10
#define black_button 11
#define silver_button 12

int white_r, white_g, white_b, black_r, black_g, black_b, blue_r, blue_g, blue_b, silver_r, silver_g, silver_b; // initialise with measured middle values
int color_threshold = 20; // Tune for best results


void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  digitalWrite(SS,HIGH);     
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  
  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  // Initialising buttons for color calibration
  pinMode(white_button, INPUT);
  pinMode(blue_button, INPUT);
  pinMode(black_button, INPUT);
  pinMode(silver_button, INPUT);

  delay(1000);
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);
  }
  // Record initial gyroscope readings when stationary as they are errors
  err_gx = gx;
  err_gy = gy;
  err_gz = gz;
  
  // Start the madgwick filter with 50 Hz sample rate
  filter.begin(50);
  
  timer = millis();
  
}

void loop() {

  //  start IMU yaw  (0x11)
  //  end IMU yaw (0x12)
  //  on ramp   (0x15)
  //  white color (0x23)
  //  black color (0x24)
  //  blue color  (0x25)
  //  silver color  (0x26)
  float red, green, blue;
  //tcs.setInterrupt(false);  // turn on LED
  delay(60);  // takes 50ms to read
  tcs.getRGB(&red, &green, &blue);
  //tcs.setInterrupt(true);  // turn off LED
  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.print(int(blue));
  Serial.print("\n");

  // Assign values of (r, g, b) for each color when its button is pressed
  if(digitalRead(white_button)) {
    white_r = int(red);
    white_g = int(green);
    white_b = int(blue);
  }
  if(digitalRead(black_button)) {
    black_r = int(red);
    black_g = int(green);
    black_b = int(blue);
  }
  if(digitalRead(blue_button)) {
    blue_r = int(red);
    blue_g = int(green);
    blue_b = int(blue);
  }
  if(digitalRead(silver_button)) {
    silver_r = int(red);
    silver_g = int(green);
    silver_b = int(blue);
  }

  // Check if (r, g, b) values are within a certain range of some color then print this color
  if (((white_r - color_threshold) < int(red) < (white_r + color_threshold)) && ((white_g - color_threshold) < int(green) < (white_g + color_threshold)) && ((white_b - color_threshold) < int(blue) < (white_b + color_threshold)))
    Serial.println("White Tile"); // else white
  else if (((black_r - color_threshold) < int(red) < (black_r + color_threshold)) && ((black_g - color_threshold) < int(green) < (black_g + color_threshold)) && ((black_b - color_threshold) < int(blue) < (black_b + color_threshold)))
    Serial.println("Black Tile");
  else if (((blue_r - color_threshold) < int(red) < (blue_r + color_threshold)) && ((blue_g - color_threshold) < int(green) < (blue_g + color_threshold)) && ((blue_b - color_threshold) < int(blue) < (blue_b + color_threshold)))
    Serial.println("Blue Tile");
  else if (((silver_r - color_threshold) < int(red) < (silver_r + color_threshold)) && ((silver_g - color_threshold) < int(green) < (silver_g + color_threshold)) && ((silver_b - color_threshold) < int(blue) < (silver_b + color_threshold)))
    Serial.println("Silver Tile");
  
  
  // Get accelometer readings
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }
  // Get gyroscope readings
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);
  }
  
  // Remove errors in gyroscope readings
  gx = gx - err_gx;  // -0.243
  gy = gy - err_gy;  // +0.12
  gz = gz - err_gz;  // +0.55

  //  Serial.print("gz: ");
  //  Serial.println(gz);
  
  // Calculate roll, pitch and yaw angles using madgwick filter
  filter.updateIMU(gx, gy, gz, ax, ay, az);
  roll = filter.getRoll();
  pitch = filter.getPitch();
  yaw = filter.getYaw();

  // Applying a complementary filter to estimate the orientation and reduce yaw drift
  yaw = ALPHA * (yaw + gz * 0.01) + (1 - ALPHA) * roll; // Complementary filter equation
  
//  Serial.print("Roll: ");
//  Serial.print(roll);
//  Serial.print(" Pitch: ");
//  Serial.print(pitch);
  Serial.print(" Yaw: ");
  Serial.println(yaw);
  
  // Checking if robot is tilted nose up to detect if on ramp
  if (abs(pitch) > 7) {
    high_pitch_count++;
    if (high_pitch_count > 20) {
      Serial.println("///////////ON RAMP////////////");
      high_pitch_count = 0;
    }
  }

    
  delay(20);

}

/*
//  // get accelerometer and gyroscope data
//  ax = ax / 1000.0;
//  ay = ay / 1000.0;
//  az = az / 1000.0;
//  gx = gx * (M_PI / 180.0);
//  gy = gy * (M_PI / 180.0);
//  gz = gz * (M_PI / 180.0);
//
//  // calculate pitch and roll angles from accelerometer data
//  pitch = atan2(-ax, sqrt(ay * ay + az * az));
//  roll = atan2(ay, az);
//
//  // calculate angular velocity around z-axis from gyroscope data
//  float wz = gz;
//
//  // calculate time difference since last iteration
//  unsigned long curr_time = millis();
//  float dt = (curr_time - prev_time) / 1000.0;
//  prev_time = curr_time;
//
//  // integrate angular velocity to obtain yaw angle
//  yaw += (wz + wz_prev) * dt / 2.0;
//  wz_prev = wz;
//
//  // apply complementary filter to combine yaw angle with pitch and roll angles
//  yaw = ALPHA * yaw + (1 - ALPHA) * atan2(-az, sqrt(ay * ay + ax * ax));//atan2(-ax, sqrt(ay * ay + az * az)
//
//  // convert yaw angle to degrees and print to serial monitor
//  float yaw_degrees = yaw * 180 / M_PI;
//  Serial.println(yaw_degrees);
//
//  delay(10);
 */
