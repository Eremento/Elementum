#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial QR_Scanner(6, 5); // TX, RX
Servo claw;
Servo arrow;
Servo air;

#define LINE_SENSOR_LEFT 4
#define LINE_SENSOR_MID 13
#define LINE_SENSOR_RIGHT 3

#define LEFT_MOTOR_PWM 9
#define RIGHT_MOTOR_PWM 10
#define LEFT_MOTOR 8
#define RIGHT_MOTOR 11

#define TRIG A0
#define ECHO A1

bool IS_BLACK_LEFT = 0;
bool IS_BLACK_MID = 0;
bool IS_BLACK_RIGHT = 0;

long duration;
int distance;
int SPEED = 90;
//char QR = "";
String QR = "";


void setup() {
  Serial.begin(9600);
  QR_Scanner.begin(9600);
  
  pinMode(LINE_SENSOR_LEFT, INPUT);
  pinMode(LINE_SENSOR_MID, INPUT);
  pinMode(LINE_SENSOR_RIGHT, INPUT);
  
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  
  pinMode(TRIG, OUTPUT);  
  pinMode(ECHO, INPUT); 

//  claw.attach(7);
//  arrow.attach(2);
//  air.attach(12);
//
//  claw.write(10);
//  delay(500);
//  arrow.write(0);
//  delay(500);
//  air.write(120);
  
}

void run() {
  analogWrite(LEFT_MOTOR_PWM,SPEED);
  analogWrite(RIGHT_MOTOR_PWM,SPEED);
}

void notrun() {
  analogWrite(LEFT_MOTOR_PWM,0);
  analogWrite(RIGHT_MOTOR_PWM,0);
}

void turn_right() {
//  digitalWrite(RIGHT_MOTOR,HIGH);
//  digitalWrite(RIGHT_MOTOR_PWM,HIGH);    
//  analogWrite(RIGHT_MOTOR_PWM,90);
//  
//  digitalWrite(LEFT_MOTOR,LOW);
//  digitalWrite(LEFT_MOTOR_PWM,HIGH);
//  analogWrite(LEFT_MOTOR_PWM,SPEED);
analogWrite(LEFT_MOTOR_PWM,SPEED);
analogWrite(RIGHT_MOTOR_PWM,0);
}

void turn_left() {
//  digitalWrite(RIGHT_MOTOR,LOW);
//  digitalWrite(RIGHT_MOTOR_PWM,HIGH);    
//  analogWrite(RIGHT_MOTOR_PWM,SPEED);
//  
//  digitalWrite(LEFT_MOTOR,HIGH);
//  digitalWrite(LEFT_MOTOR_PWM,HIGH);
//  analogWrite(LEFT_MOTOR_PWM,90);
analogWrite(LEFT_MOTOR_PWM,0);
analogWrite(RIGHT_MOTOR_PWM,SPEED);
}

void pick_up() {
   claw.write(90);
   delay(800);
   air.write(120);
   delay(800);
   arrow.write(120);
   delay(800);
   claw.write(10);
   delay(800);
   air.write(180);
   delay(800);
   arrow.write(0);
}

void loop() {
  IS_BLACK_RIGHT = digitalRead(LINE_SENSOR_RIGHT);
  IS_BLACK_MID = digitalRead(LINE_SENSOR_MID);
  IS_BLACK_LEFT = digitalRead(LINE_SENSOR_LEFT);
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  
  distance= duration*0.034/2;
//  Serial.print("distation ");
//  Serial.println(distance);


//  if (distance == 20){
//    if (QR_Scanner.available()) 
//  {
//    while (QR_Scanner.available()) 
//    {
////      char QR = QR_Scanner.read(); 
////      QRstring += QR; 
//      char i = QR_Scanner.read(); 
//      QR += i; 
//    }
//    Serial.println(QR);
//  }
//  if (QR.indexOf("c") == 0) {
//    pick_up();
//    Serial.println("test");
//  }
//  }
  
  if (IS_BLACK_LEFT==0 && IS_BLACK_RIGHT==0 && IS_BLACK_MID==1) {
    run();
    Serial.println("run");
  }
  else if (IS_BLACK_LEFT==0 && IS_BLACK_RIGHT==1) {
    turn_left();
    Serial.println("left");
  }
  else if (IS_BLACK_LEFT==1 && IS_BLACK_RIGHT==0) {
    turn_right();
    Serial.println("right");
  }
  else{
    notrun();
    Serial.println("not");
  }
  delay(50);
}
