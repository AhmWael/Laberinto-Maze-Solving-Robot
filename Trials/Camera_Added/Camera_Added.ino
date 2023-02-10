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

Servo myservo;

String received_dist_1, received_dist_2, received_dist_3;
int TOF_R, TOF_L, TOF_C;

int pwm_L = 0;
int pwm_R = 0;

bool left_turn = 0;

unsigned long long int timer;
int tile_length = 2330;
volatile int posir = 0, posil = 0;

//Digital Communication Nano Color
#define Col_1_pin 35
#define Col_2_pin 31
int Col_1, Col_2;

bool blue_flag = 0;
int blue_counter = 0;

bool black_flag = 0;
int black_counter = 0;

//Digital Communication Right Camera
#define Cam_1_R_pin 51 //Left_bit //27    7 -- 49
#define Cam_2_R_pin 53 //Cen0ter_bit //29  8 -- 47
#define Cam_3_R_pin 47 //Right_bit //31   9 -- 45
bool Cam_1_L, Cam_2_L, Cam_3_L, Cam_1_R, Cam_2_R, Cam_3_R;

#define buzzer 45

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

  pinMode(Cam_1_R_pin, INPUT);
  pinMode(Cam_2_R_pin, INPUT);
  pinMode(Cam_3_R_pin, INPUT);

  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, LOW);

  myservo.attach(37);
  myservo.write(62);
  

  timer = millis();
  while (millis() - timer <= 2500) {
    read_all_TOFs();
    MoveWheels(HIGH, 0, HIGH, 0, "Stop");
  }
  timer = millis();
}

void loop() {
  while (millis() - timer <= 750) {
    read_all_TOFs();
  }
  Solve();
}
