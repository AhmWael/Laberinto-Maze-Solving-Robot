#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>

#define ENCAr 3 // YELLOW
#define ENCBr 2 // WHITE
#define r_pwm 12
#define l_dir 9
#define ENCAl 21 // YELLOW
#define ENCBl 20 // WHITE
#define l_pwm 10
#define r_dir 11

#define turn_angle_L 2900
#define turn_angle_R 2550

Servo myservo;

String received_dist_1, received_dist_2, received_dist_3;
int TOF_R, TOF_L, TOF_C;

int pwm_L = 0;
int pwm_R = 0;

bool left_turn = 0;

unsigned long long int timer;
//int tile_length = 2330;
volatile int posir = 0, posil = 0;

int X_Position = 20;
int Y_Position = 20;
int Direction = 0; // North
bool Start_Tile = 1;
/*
 * 0 -> North
 * 1 -> East
 * 2 -> South
 * 3 -> West
 */

//Digital Communication Nano Color
#define Col_1_pin 35
#define Col_2_pin 31
int Col_1, Col_2;

bool blue_flag = 0;
int blue_counter = 0;

bool black_flag = 0;
int black_counter = 0;

int right_counter = 0;
int posir_tmp, posil_tmp;

//Digital Communication Right Camera
#define Cam_1_R_pin 51 //Left_bit //27    7 -- 49
#define Cam_2_R_pin 53 //Cen0ter_bit //29  8 -- 47
#define Cam_3_R_pin 47 //Right_bit //31   9 -- 45
bool Cam_1_L, Cam_2_L, Cam_3_L, Cam_1_R, Cam_2_R, Cam_3_R;
#define X 30
#define Y 30
bool Maze[X][Y][6];
int Unvisited[50];
short Minimum_X = X, Minimum_Y = Y;
short Maximum_X = 0, Maximum_Y = 0;
/*
 * [0, 3] -> up wall, right wall, down wall, left wall
 * [4] -> Visited tile or not
 * [5] -> victim or not
 */
#define buzzer 45

#define ir_obstacle_left 43
#define ir_obstacle_right 41
#define wall_detector_left 33
#define wall_detector_right 29
#define tilt_asc 39

bool tilt = 1;
int tilt_count = 0;

void setup() {
  Serial.begin(115200);
  //  Serial1.begin(115200);//9600
  Serial2.begin(115200);//9600
  Serial3.begin(115200);//9600
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

  pinMode(Col_1, INPUT);
  pinMode(Col_2, INPUT);

  pinMode(Cam_1_R_pin, INPUT_PULLUP);
  pinMode(Cam_2_R_pin, INPUT_PULLUP);
  pinMode(Cam_3_R_pin, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, LOW);

  myservo.attach(37);
  myservo.write(55);
  
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
  for(int i = 0; i < X; i++)
    for(int j = 0; j < Y; j++)
      for(int k = 0; k < 6; k++)
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
  Solve();
}
