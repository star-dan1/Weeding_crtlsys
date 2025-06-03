#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// DC motor
#define in1 12
#define in2 13
#define in3 15
#define in4 2
#define en1 14
#define en3 4

// DC motor for weeding
#define SIN1 19
int speed = HIGH;
int noSpeed = LOW;



//for ultrasonic
const int trigpin = 34;
const int echopin = 35;

long duration;
int distance;
int newDis;
const float offset = 12.5;

void cut() {
  digitalWrite(SIN1, speed);
}

void cutStop() {
  digitalWrite(SIN1, noSpeed);
}

int ultraSense() {
  digitalWrite(trigpin, LOW);
  delay(2);
  digitalWrite(trigpin, HIGH);
  delay(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = duration / 29 / 2;
  newDis = distance - offset;
  Serial.println(newDis);
  delay(100);

  // return newDis;
}

int moveForword() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(en1, 150);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(en3, 0);
}

int moveBackward() {
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(en1, 0);

  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(en3, 150);
}

int moveright() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(en1, 150);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(en3, 30);
}

int moveleft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(en1, 30);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(en3, 150);
}

int stop() {
  digitalWrite(in2, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(en1, 0);

  digitalWrite(in4, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(en3, 0);
}

 void fwd_Print(){
  lcd.autoscroll();
  lcd.print("Moving Forward");
  
 }

 void turn_left_Print(){
  lcd.autoscroll();
  lcd.print("Moving left");
  
 }

 void turn_right_Print(){
  lcd.autoscroll();
  lcd.print("Moving right");
  
 }

 void op_done_Print(){
  lcd.autoscroll();
  lcd.print("Operation done");
  
 }


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // LCD set_up
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  //other pins
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en3, OUTPUT);
  pinMode(SIN1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  stop();
  cutStop();
  delay(500);
  cut();
  moveForword();

  if (ultraSense() <= offset) {
    moveleft();
    turn_left_Print();
    delay(500);
    moveleft();
    turn_left_Print();
    delay(500);
    moveForword();
    fwd_Print();


    if (ultraSense() <= offset) {
      moveright();
      turn_right_Print();
      delay(500);
      moveright();
      turn_left_Print();
      delay(500);
      moveForword();
      fwd_Print();

      if (ultraSense() <= offset) {
        moveleft();
        turn_left_Print();
        delay(500);
        moveleft();
        turn_left_Print();
        delay(500);
        moveForword();
        fwd_Print();

        if (ultraSense() <= offset) {
          moveright();
          turn_right_Print();
          delay(500);
          moveright();
          turn_right_Print();
          delay(500);
          moveForword();
          fwd_Print();

          stop();
          cutStop();
          op_done_Print();
        }
      }
    }
  };
}
