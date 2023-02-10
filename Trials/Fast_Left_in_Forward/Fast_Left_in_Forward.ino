#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCAr 3 // YELLOW
#define ENCBr 2 // WHITE
#define r_pwm 12
#define l_dir 9
#define ENCAl 21 // YELLOW
#define ENCBl 20 // WHITE
#define l_pwm 10
#define r_dir 11


String received_dist_1, received_dist_2, received_dist_3;
int TOF_R, TOF_L, TOF_C;

int pwm_L = 0;
int pwm_R = 0;

bool left_turn = 0;

unsigned long long int timer;
int tile_length = 2330;
volatile int posir = 0, posil = 0;

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
