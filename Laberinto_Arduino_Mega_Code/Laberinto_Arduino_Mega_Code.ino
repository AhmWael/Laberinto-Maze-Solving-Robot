/******* Needed Libraries *******/
#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>
#include "Adafruit_VL53L0X.h"
//////////////////////////////////
/******* Debug *******/
#define debug_cam 0
#define debug_color 0
#define debug_TOF 0
#define debug_encoder 0
#define debug_mapping 0
///////////////////////
/******* Motor Driver & Encoder pins *******/
#define ENCAr 19 // YELLOW
#define ENCBr 18 // WHITE
#define r_pwm 10
#define r_dir 9
#define ENCAl 2 // YELLOW
#define ENCBl 3 // WHITE
#define l_pwm 12
#define l_dir 11
/////////////////////////////////////////////
#define turn_angle_L 2900
#define turn_angle_R 2550

Servo myservo; // creating servo object
/******* Needed variables to read TOF readings *******/
//String received_dist_1, received_dist_2, received_dist_3;
//int TOF_R, TOF_L, TOF_C;
/******* addresses assigned to each sensor *******/
// addresses assigned to each sensor
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33
#define LOX5_ADDRESS 0x34

int TOF_L, TOF_C_L, TOF_C_R, TOF_R, TOF_R_F;

// set the pins to shutdown
#define SHT_LOX1 23
#define SHT_LOX2 27
#define SHT_LOX3 29
#define SHT_LOX4 33
#define SHT_LOX5 25

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox5 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;
VL53L0X_RangingMeasurementData_t measure5;
///////////////////////////////////////////////////

int pwm_L = 0;
int pwm_R = 0;

bool left_turn = 0;

unsigned long long int timer;

volatile int posir = 0, posil = 0; // encoder readings are stored here

/******* Color Nano Pins & Variables *******/
#define Col_1_pin 35
#define Col_2_pin 31
int Col_1, Col_2;

bool blue_flag = 0;
int blue_counter = 0;

bool black_flag = 0;
int black_counter = 0;

int right_counter = 0;
int posir_tmp, posil_tmp;
/////////////////////////////////////////////
/******* Camera Pins & Variable *******/
#define Cam_1_R_pin 51 //Left_bit //27    7 -- 49
#define Cam_2_R_pin 53 //Cen0ter_bit //29  8 -- 47
#define Cam_3_R_pin 47 //Right_bit //31   9 -- 45
bool Cam_1_L, Cam_2_L, Cam_3_L, Cam_1_R, Cam_2_R, Cam_3_R;
////////////////////////////////////////
/******* Mapping Variables *******/
int X_Position = 20; // at start
int Y_Position = 20; // at start
int Direction = 0;
/*
 * 0 -> North
 * 1 -> East
 * 2 -> South
 * 3 -> West
 */
bool Start_Tile = 1;
#define X 30
#define Y 30
bool Maze[X][Y][6];
short Unvisited[50];
short Minimum_X = X, Minimum_Y = Y;
short Maximum_X = 0, Maximum_Y = 0;
/*
 * [0, 3] -> up wall, right wall, down wall, left wall
 * [4] -> Visited tile or not
 * [5] -> victim or not
 */
///////////////////////////////////
/******* LED & Buzzer PCB pin *******/
#define buzzer 45
//////////////////////////////////////
/******* Obstacle IR & Tilt Sensor Pins & Variables *******/
#define ir_obstacle_left 43
#define ir_obstacle_right 41
#define wall_detector_left 33
#define wall_detector_right 29
#define tilt_asc 39

bool tilt = 1;
int tilt_count = 0;
////////////////////////////////////////////////////////////
void setup() {
  // Pins are being set to either an input or an output
  // Initialise serial communication
  Serial.begin(115200);
  //  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  //////////////////////////////////////////////////////////////////
  // wait until serial port opens for native USB devices
  while (! Serial) { delay(1); }

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);
  pinMode(SHT_LOX5, OUTPUT);

  Serial.println("Shutdown pins inited...");

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);

  Serial.println("Both in reset mode...(pins are low)");


  Serial.println("Starting...");
  setID();
  //////////////////////////////////////////////////////////////////////

  pinMode(l_pwm, OUTPUT);
  pinMode(r_pwm, OUTPUT);
  pinMode(l_dir, OUTPUT);
  pinMode(r_dir, OUTPUT);
  pinMode(ENCAr, INPUT);
  pinMode(ENCBr, INPUT);
  pinMode(ENCAl, INPUT);
  pinMode(ENCBl, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCAr), readEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCAl), readEncoder2, RISING);

  pinMode(Col_1_pin, INPUT);
  pinMode(Col_2_pin, INPUT);

  pinMode(Cam_1_R_pin, INPUT_PULLUP);
  pinMode(Cam_2_R_pin, INPUT_PULLUP);
  pinMode(Cam_3_R_pin, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, LOW);

  myservo.attach(37); // attach the servo
  myservo.write(55); // neutral angle
  
  pinMode(ir_obstacle_left, INPUT);
  pinMode(ir_obstacle_right, INPUT);
  pinMode(wall_detector_left, INPUT);
  pinMode(wall_detector_right, INPUT);
  pinMode(tilt_asc, INPUT);

  timer = millis();
  while (millis() - timer <= 2500) {
    read_all_TOFs();
    MoveWheels(HIGH, 0, HIGH, 0, "Stop");
  }
  for(short i = 0; i < X; i++)
    for(short j = 0; j < Y; j++)
      for(short k = 0; k < 6; k++)
        Maze[i][j][k] = 0;
  timer = millis();
}

void loop() {
//  Serial.print("wall_detector_right: ");
//  Serial.println(digitalRead(wall_detector_right));
  while (millis() - timer <= 750) {
    read_all_TOFs();
  }
  Serial.print(X_Position);
  Serial.print(", ");
  Serial.print(Y_Position);
  Serial.println();
  Solve(); // This is the main function
}
