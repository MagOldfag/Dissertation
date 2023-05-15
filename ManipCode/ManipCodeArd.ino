#include "iarduino_MultiServo.h"

iarduino_MultiServo MSS;

void setup() {
  MSS.servoSet(1, SERVO_MG996R);
  MSS.servoSet(2, SERVO_MG996R);
  //MSS.servoSet(3, 180, 50, 2500);
  MSS.servoSet(3, SERVO_MG996R);
  MSS.servoSet(4, 180, 100, 500);
  MSS.servoSet(5, 180, 100, 500);
  MSS.servoSet(6, SERVO_MG996R);
  //MSS.servoSet(7, 180, 800,2200);
  MSS.servoSet(7, SERVO_MG996R);
  MSS.begin();
  MSS.servoWrite(1,40);
  MSS.servoWrite(2,0);
  MSS.servoWrite(3,0);
  MSS.servoWrite(4,45);
  MSS.servoWrite(5,35);
  MSS.servoWrite(6,50);
  MSS.servoWrite(7,0);

  Serial.begin (9600);

  pinMode(13, 1);
}

int i = 1;
int value = 0;

void loop() {

  if (Serial.available()) {
    char thisChar = Serial.read();
    if (thisChar == '(') {
      value = 0;
      i = 1;
      return;
    }
    if (thisChar == ',' || thisChar == ')') {
      Serial.println(String(i) + "-" + String(value));

      MSS.servoWrite(i,value);
   
      i++;
      value = 0;
      return;
    }
    if (thisChar == '-') {
      value = -value;
      return;
    }   
    value = value * 10 + (thisChar - '0');
  }
}
