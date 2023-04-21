#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>

int started = 0;

#define ENCAr 3 // YELLOW
#define ENCBr 2 // WHITE
#define r_pwm 12
#define l_dir 9
#define ENCAl 21 // YELLOW
#define ENCBl 20 // WHITE
#define l_pwm 10
#define r_dir 11

Servo myservo;

//TOF Serial Communication
String received_dist_1, received_dist_2, received_dist_3;
int TOF_R, TOF_L, TOF_C;

int pwm_L = 0;
int pwm_R = 0;

// Encoder data initialisation
int left_pwm = 0;
int right_pwm = 0;
int general_pwm = -1;
unsigned long long int timer;
int tile_length = 1000;
volatile int posir = 0, posil = 0, posil2 = 0; 
long prevT = 0;
float eprev = 0;
float eintegral = 0;
int turn_rounds = 2;

int black_count = 0;
bool last_blue = false;

//Digital Communication Right Camera
#define Cam_1_R_pin 51 //Left_bit //27    7 -- 49
#define Cam_2_R_pin 53 //Cen0ter_bit //29  8 -- 47
#define Cam_3_R_pin 47 //Right_bit //31   9 -- 45
bool Cam_1_L, Cam_2_L, Cam_3_L, Cam_1_R, Cam_2_R, Cam_3_R, Col_1, Col_2;

//Tilt Sensor Pins
#define tilt_f 39
#define tilt_b 43

//Digital Communication Nano Color
#define Col_1_pin 35
#define Col_2_pin 31

#define buzzer 45

int robot_dir = 0; // 0 --> North, 1 --> East, 2 --> South, 3 --> West
int x_maze = 30, y_maze = 30;
int x_max = 30, x_min = 30, y_max = 30, y_min = 30;
char maze[60][60];

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

  myservo.attach(37);
  myservo.write(62);
  
  //  pinMode(PWM,OUTPUT);
  //  pinMode(IN1,OUTPUT);
  //  pinMode(IN2,OUTPUT);
  pinMode(Cam_1_R_pin, INPUT);
  pinMode(Cam_2_R_pin, INPUT);
  pinMode(Cam_3_R_pin, INPUT);

  pinMode(tilt_f, INPUT);
  pinMode(tilt_b, INPUT);

  pinMode(Col_1, INPUT);
  pinMode(Col_2, INPUT);
  
  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, LOW);

  initialise_the_map();

  //  Serial.println("target pos");
  delay(2500);
  timer = millis();
}

void loop() {
 /*
    if (Serial2.available()) {
     received_dist_2 = Serial2.readStringUntil('\n');
     //Serial.println(received_dist);
     TOF_C = received_dist_2.toInt();
     //Serial.println(TOF_C);
     Serial.print("TOF_C : ");
     Serial.println(TOF_C);
    }

    if (Serial3.available()) {
     received_dist_3 = Serial3.readStringUntil('\n');
     //Serial.println(received_dist);
     TOF_R = received_dist_3.toInt();
     //Serial.println(TOF_R);
     Serial.print("TOF_R : ");
     Serial.println(TOF_R);
    }
    */
    //  if (general_pwm == -1) {
    //    timer = millis();
    //    general_pwm = 4;
    //    left_pwm = general_pwm;
    //    right_pwm = general_pwm;
    //  }
    //  else if ((general_pwm + 25 <= 254) && (millis() - timer >= 100)) {
    //    timer = millis();
    //    general_pwm += 25;
    //    left_pwm = general_pwm;
    //    right_pwm = general_pwm;
    //  }

    //  if (((posir + posil2) / 2) >= (2372 * 1)) {
    //    analogWrite(l_pwm, 0);
    //    digitalWrite(l_dir, HIGH);
    //    analogWrite(r_pwm, 0);
    //    digitalWrite(r_dir, HIGH);
    //    Serial.println("New Tile Reached");
    //    delay(1000);
    //    general_pwm = -1;
    //    posir = 0;
    //    posil = 0;
    //    //tile ++;
    //  }
    //pwm_L = min(max(150, 150 * (abs((TOF_R/85)))), 254);


/*
    if (TOF_R <= 85)
    {
     pwm_L = max(94, 94 + ((TOF_R - 35) / 50.0) * 80.0);
     pwm_R = min(254, 254 - ((TOF_R - 35) / 50.0) * 54.0);
    }
    else if ((TOF_R > 85) && (TOF_R <= 135))
    {
     pwm_L = max(174, 174 + ((TOF_R - 85) / 50.0) * 80.0);
     pwm_R = max(200, 200 - ((TOF_R - 85) / 50.0) * 54.0);
    }
    else {
     pwm_R = 200;
     pwm_L = 174;
    }
    analogWrite(l_pwm, pwm_L);
    digitalWrite(l_dir, HIGH);
    analogWrite(r_pwm, pwm_R);
    digitalWrite(r_dir, HIGH);
    Serial.print("TOF:");
    Serial.print(TOF_R);
    Serial.print("\t");
    Serial.print("Left PWM: ");
    Serial.print(pwm_L);
    Serial.print("     ");
    Serial.print("Right PWM: ");
    Serial.print(pwm_R);
    Serial.println();*/
    /*analogWrite(l_pwm, min(max(150, 150 * (abs((TOF_R/85)))), 254));
     digitalWrite(l_dir, HIGH);
     analogWrite(r_pwm, 254);
     digitalWrite(r_dir, 1 - (TOF_R > 150));*/



  //  int a = digitalRead(ENCAl), b = digitalRead(ENCBl), c = digitalRead(ENCAr), d = digitalRead(ENCBr);
  //  Serial.print("posil: ");
  //  Serial.print(posil2);
  //  Serial.print("\tposir: ");
  //  Serial.println(posir);
  //  Serial.println();


  //  Serial.print("PWM_R: ");
  //  Serial.println(right_pwm);
  //  Serial.print("PWM_L: ");
  //  Serial.println(left_pwm);
  if (started == -1) {
    MoveWheels(LOW, 0, LOW, 0, "Stop");
    return ;
  }
  while (millis() - timer <= 750) {
  read_all_TOFs();
  }
  Solve();
  if (started == 0)
    started = 1;
}
