//Arduino Bluetooth Controlled Car Video - https://www.youtube.com/watch?v=BbASlFelJSQ //
//// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
#include<NewPing.h>
#include <AFMotor.h>
#define trig1 A0
#define echo1 A1
#define trig2 A2
#define echo2 A3
#define trig3 A4
#define echo3 A5
#define max_dis 250
NewPing sonar1(trig1, echo1, max_dis);
NewPing sonar2(trig2, echo2, max_dis);
NewPing sonar3(trig3,echo3,max_dis);
//initial motors pin
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
long tocm1, tocm2,tocm3;
int Break1,start;
void setup()
{
  pinMode(8, OUTPUT);
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  tocm1 = microsecondsToCentimeters1(); tocm2 = microsecondsToCentimeters2();
  tocm3 = microsecondsToCentimeters3();
}

void loop() {
  char command = 's';
  if (Serial.available() > 0) {
    command = Serial.read();
    //    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.
   
    switch (command) {
      case 'X':Serial.println(command);buzzer();delay(100);buzzerstop();start=1;break;
      case 'x':Serial.println(command);buzzer();delay(100);buzzerstop();start=-1;motor1.run(RELEASE);
      motor2.run(RELEASE);motor3.run(RELEASE);
      motor3.setSpeed(0);
      motor4.run(RELEASE);break;
        case 'F':
        if(start==1){Serial.println(command);
        forward();Break1=1;
         tocm1 = microsecondsToCentimeters1();
         tocm2 = microsecondsToCentimeters2();
         if (tocm1<15||tocm2<15)
        { buzzer();back();
          delay(50);buzzerstop();
          Stop();
        }
         else
        {
          buzzerstop();
        }}
        break;
      case 'B':if(start==1){Serial.println(command);
       back();Break1=0;
         tocm3 = microsecondsToCentimeters3();
        if (tocm3 < 15)
        { buzzer();forward();
          delay(50);buzzerstop();Stop();
        }
        else
        {
          buzzerstop();
         
        }}
        break;
      case 'L':if(start==1){
        Serial.println(command);
        digitalWrite(8, HIGH);
        left();}
        break;
      case 'R':if(start==1){
        Serial.println(command);
        right();}
        break;
      case 'I':if(start==1){
        Serial.println(command);
        rightforward(); tocm1 = microsecondsToCentimeters1();
         tocm2 = microsecondsToCentimeters2(); if (tocm1<15||tocm2<15)
        { buzzer();back();
          delay(50);buzzerstop();
          Stop();
        }
         else
        {
          buzzerstop();
        }Break1=1;}break;
      case 'W': if(start==1){Serial.println(command);motor2.setSpeed(255);
        motor2.run(FORWARD);} break;
      case 'w': if(start==1){motor2.setSpeed(0);
        motor2.run(RELEASE); }break;
      case 'G': if(start==1){Serial.println(command);
        leftforward(); tocm1 = microsecondsToCentimeters1();
         tocm2 = microsecondsToCentimeters2();if (tocm1<15||tocm2<15)
        { buzzer();back();
          delay(50);buzzerstop();
          Stop();
        }
         else
        {
          buzzerstop();
        } Break1=1;}break;
      case 'H': if(start==1){Serial.println(command);
        leftbackward();tocm3 = microsecondsToCentimeters3();
        if (tocm3 < 15)
        { buzzer();forward();
          delay(50);buzzerstop();Stop();
        }
        else
        {
          buzzerstop();
         
        }Break1=0;} break;
      case 'J': if(start==1){Serial.println(command);
        rightbackward();tocm3 = microsecondsToCentimeters3();
        if (tocm3 < 15)
        { buzzer();forward();
          delay(50);buzzerstop();Stop();
        }
        else
        {
          buzzerstop();
         
        }Break1=0;} break;
      case 'V':if(start==1){Serial.println(command);buzzer();} break;
      case 'v': if(start==1){Serial.println(command); buzzerstop();} break;
      case 'U':if(start==1){Serial.println(command);motor3.run(BACKWARD);motor3.setSpeed(255);
      if(Break1==1)
      {
        back();delay(50);motor4.run(RELEASE);
      }
      if(Break1==0)
      {
        forward();delay(50);motor4.run(RELEASE);
      }
      if(Break1==2)
      {
        motor4.run(RELEASE);
      }} break;
      case 'u':if(start==1){Serial.println(command); 
      motor3.run(RELEASE);Break1=2;}break;
      case 'D':motor1.run(RELEASE);motor2.run(RELEASE);motor3.run(RELEASE);motor3.setSpeed(0);motor4.run(RELEASE);
      default://Serial.println(command);
      digitalWrite(8, LOW); Stop();
    }
  }
}


void rightforward()
{
  motor4.setSpeed(255);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);
}
void leftforward()
{
  motor4.setSpeed(255);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD);
}
void rightbackward()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD);
}
void leftbackward()
{
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD);
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD);
}
void forward()
{

  /*motor1.setSpeed(255); //Define maximum velocity
    motor1.run(FORWARD); //rotate the motor clockwise
    motor2.setSpeed(255); //Define maximum velocity
    motor2.run(FORWARD); //rotate the motor clockwise
    motor3.setSpeed(255);//Define maximum velocity
    motor3.run(FORWARD);*/ motor1.run(RELEASE);
  motor4.setSpeed(255);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  /* motor1.setSpeed(255); //Define maximum velocity
    motor1.run(BACKWARD); //rotate the motor anti-clockwise
    motor2.setSpeed(255); //Define maximum velocity
    motor2.run(BACKWARD); //rotate the motor anti-clockwise
    motor3.setSpeed(255); //Define maximum velocity
    motor3.run(BACKWARD);*/  motor1.run(RELEASE);
    motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void left()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); 
    motor4.setSpeed(0); //Define maximum velocity
  motor4.run(RELEASE); //rotate the motor anti-clockwise
   //Define minimum velocity
    /*motor2.setSpeed(255); //Define maximum velocity
    motor2.run(BACKWARD); //rotate the motor anti-clockwise
    motor3.setSpeed(255); //Define maximum velocity
    motor3.run(FORWARD);  //rotate the motor clockwise
    motor4.setSpeed(255); //Define maximum velocity
    motor4.run(FORWARD);*/  //rotate the motor clockwise
}

void right()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);   motor4.setSpeed(0); //Define maximum velocity
  motor4.run(RELEASE); //rotate the motor clockwise
  //Define minimum velocity
  /* motor2.setSpeed(255); //Define maxqimum velocity
    motor2.run(FORWARD); //rotate the motor clockwise
    motor3.setSpeed(255); //Define maximum velocity
    motor3.run(BACKWARD); //rotate the motor anti-clockwise
    motor4.setSpeed(255); //Define maximum velocity
    motor4.run(BACKWARD);*/ //rotate the motor anti-clockwise
}

void Stop()
{
  /* motor1.setSpeed(0); //Define minimum velocity
    motor1.run(RELEASE); //stop the motor when release the button
    motor2.setSpeed(0); //Define minimum velocity
    motor2.run(RELEASE); //rotate the motor clockwise
    motor3.setSpeed(0); //Define minimum velocity
    motor3.run(RELEASE);*/ //stop the motor when release the button
  motor1.setSpeed(0); motor1.run(RELEASE);
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}
long microsecondsToCentimeters1()
{
  int cm = sonar1.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}
long microsecondsToCentimeters2()
{
  int cm = sonar2.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}
long microsecondsToCentimeters3()
{
  int cm = sonar3.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}
void buzzer()
{

  motor3.run(FORWARD);
  motor3.setSpeed(40);
}
void buzzerstop()
{
  motor3.run(RELEASE);
}
