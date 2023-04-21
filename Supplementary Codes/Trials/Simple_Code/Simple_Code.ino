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

int left_pwm = 0;
int right_pwm = 0;
int general_pwm = -1;
unsigned long long int timer;
int tile_length = 1000;
volatile int posir = 0, posil = 0, posil2 = 0; // specify posi as volatile: https://w...content-available-to-author-only...o.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;

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

  //  pinMode(PWM,OUTPUT);
  //  pinMode(IN1,OUTPUT);
  //  pinMode(IN2,OUTPUT);

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
  while (millis() - timer <= 750) {
  read_all_TOFs();
  }
  Solve();
}
