#include <Servo.h>
Servo S1; Servo S2; Servo S3; Servo S4; Servo S5; Servo S6;

#define btnPin8 8
#define btnPin9 9
#define btnPin10 10

//кнопки и счётчик градусов
bool flag8 = false;
uint32_t btnTimer8 = 0;
bool flag9 = false;
uint32_t btnTimer9 = 0;
int count = 0;
bool flag10 = false;
uint32_t btnTimer10 = 0;
bool isButton=true;


  //Длины и расстояния
  float a3=20;
  float a4=15;
  float d1=10;
  float d5=5;

  //Углы
  float t1d=0;
  float t2d=0;
  float t3d=0;
  float t4d=0;
  float t5d=0;
  float t6d=0;
  float pi=3.141592654; 

//Известные параметры
float nx; float ny; float nz;
float ox; float oy; float oz;
float ax; float ay; float az;

  
//Неизвестные параметры
float px; //Итоговое значение координаты X
float py; //Итоговое значение координаты Y
float pz; //Итоговое значение координаты Z

void setup()
{
  Serial.begin(9600);
//Подключение сервоприводов
    S1.attach(2);
  S2.attach(3);
    S3.attach(4);
  S4.attach(5);
  S5.attach(6);
  S6.attach(7);
  
  pinMode(btnPin8,INPUT);
  pinMode(btnPin9,INPUT);
  pinMode(btnPin10,INPUT);


void loop()
{

  if(isButton){
    S1.write(constrain(count,0,36)*5);}
  else{
    t1d = map(analogRead(A0),0,1023,0,180);
    S1.write(t1d);
  }
  //S2.write(t2*(180/pi));
  t2d = map(analogRead(A1),0,1023,0,180);
  S2.write(t2d);
  //S3.write(t3*(180/pi));
  t3d = map(analogRead(A2),0,1023,0,180);
  S3.write(t3d);
  //S4.write(t4*(180/pi));
  t4d = map(analogRead(A3),0,1023,0,180);
  S4.write(t4d);
  //S5.write(t5*(180/pi));
  t5d = map(analogRead(A4),0,1023,0,180);
  S5.write(t5d);
  //S6.write(t6*(180/pi));
  t6d = map(analogRead(A5),0,1023,0,180);
  S6.write(t6d);
  
  bool btnState8 = digitalRead(btnPin8);
  bool btnState9 = digitalRead(btnPin9);
  bool btnState10 = digitalRead(btnPin10);
  
  if (btnState8 && !flag8){
    flag8 = true;
    count++;
  }
  
  if (btnState8 && flag8 && millis() - btnTimer8 > 50) {
    btnTimer8 = millis();
    count++;
  }
  
  if(!btnState8 && flag8){
    flag8=false;
  }
  
  if (btnState9 && !flag9){
    flag9 = true;
    count--;
  }
  
  if (btnState9 && flag9 && millis() - btnTimer9 > 50) {
    btnTimer9 = millis();
    count--;
  }
  
  if(!btnState9 && flag9){
    flag9=false;
  }
  if (btnState10 && !flag10){
    flag10 = true;
    forwardKinematics(count,t2d,t3d,t4d,t5d,t6d);
  }
  if (btnState10 && flag10 && millis() - btnTimer10 > 200) {
  isButton = !isButton;
  }
  if(!btnState10 && flag10){
    flag10=false;
  }
  
}

void forwardKinematics(float t1d,float t2d,float t3d,float t4d,float t5d,float t6d){
  
    float t1=t1d*pi/180;
    float t2=t2d*pi/180;
    float t3=t3d*pi/180;
    float t4=t4d*pi/180;
    float t5=t5d*pi/180;
    float t6=t6d*pi/180;
  
    nx = -cos(t6)*(cos(t5)*(cos(t3)*cos(t4)*(sin(t1)*sin(t2) - cos(t1)*cos(t2)) - sin(t3)*sin(t4)*(sin(t1)*sin(t2) - cos(t1)*cos(t2))) - sin(t5)*(cos(t3)*sin(t4)*(sin(t1)*sin(t2) - cos(t1)*cos(t2)) + cos(t4)*sin(t3)*(sin(t1)*sin(t2) - cos(t1)*cos(t2)))) - sin(t6)*(cos(t1)*sin(t2) + cos(t2)*sin(t1));
  ny = cos(t6)*(cos(t5)*(cos(t3)*cos(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) - sin(t3)*sin(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1))) - sin(t5)*(cos(t3)*sin(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) + cos(t4)*sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))) - sin(t6)*(sin(t1)*sin(t2) - cos(t1)*cos(t2));
  nz = cos(t6)*(cos(t5)*(cos(t3)*sin(t4) + cos(t4)*sin(t3)) - sin(t5)*(sin(t3)*sin(t4) - cos(t3)*cos(t4)));
  
  ox = sin(t6)*(cos(t5)*(cos(t3)*cos(t4)*(sin(t1)*sin(t2) - cos(t1)*cos(t2)) - sin(t3)*sin(t4)*(sin(t1)*sin(t2) - cos(t1)*cos(t2))) - sin(t5)*(cos(t3)*sin(t4)*(sin(t1)*sin(t2) - cos(t1)*cos(t2)) + cos(t4)*sin(t3)*(sin(t1)*sin(t2) - cos(t1)*cos(t2)))) - cos(t6)*(cos(t1)*sin(t2) + cos(t2)*sin(t1));
  oy = - sin(t6)*(cos(t5)*(cos(t3)*cos(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) - sin(t3)*sin(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1))) - sin(t5)*(cos(t3)*sin(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) + cos(t4)*sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))) - cos(t6)*(sin(t1)*sin(t2) - cos(t1)*cos(t2));
  oz = -sin(t6)*(cos(t5)*(cos(t3)*sin(t4) + cos(t4)*sin(t3)) - sin(t5)*(sin(t3)*sin(t4) - cos(t3)*cos(t4)));

  ax = cos(t5)*(cos(t3)*sin(t4)*(sin(t1)*sin(t2) - cos(t1)*cos(t2)) + cos(t4)*sin(t3)*(sin(t1)*sin(t2) - cos(t1)*cos(t2))) + sin(t5)*(cos(t3)*cos(t4)*(sin(t1)*sin(t2) - cos(t1)*cos(t2)) - sin(t3)*sin(t4)*(sin(t1)*sin(t2) - cos(t1)*cos(t2)));
  ay = - cos(t5)*(cos(t3)*sin(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) + cos(t4)*sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1))) - sin(t5)*(cos(t3)*cos(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) - sin(t3)*sin(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)));
  az = - cos(t5)*(sin(t3)*sin(t4) - cos(t3)*cos(t4)) - sin(t5)*(cos(t3)*sin(t4) + cos(t4)*sin(t3));

  
//Вычисление неизвестных параметров, используя уравнение
  px = d5*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) - cos(t3)*a3*(sin(t1)*sin(t2) - cos(t1)*cos(t2)) - cos(t3)*cos(t4)*a4*(sin(t1)*sin(t2) - cos(t1)*cos(t2)) + sin(t3)*sin(t4)*a4*(sin(t1)*sin(t2) - cos(t1)*cos(t2));
  py = d5*(sin(t1)*sin(t2) - cos(t1)*cos(t2)) + cos(t3)*a3*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) + cos(t3)*cos(t4)*a4*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) - sin(t3)*sin(t4)*a4*(cos(t1)*sin(t2) + cos(t2)*sin(t1));
  pz = d1 + sin(t3)*a3 + cos(t3)*sin(t4)*a4 + cos(t4)*sin(t3)*a4;
 
 
//Вывод координат в серийный порт
    Serial.print("X= "); Serial.println(px,DEC);
    Serial.print("Y= "); Serial.println(py,DEC);
    Serial.print("Z= "); Serial.println(pz,DEC);
}
