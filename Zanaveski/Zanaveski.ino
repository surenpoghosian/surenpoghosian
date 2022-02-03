//После подключения Ардуино упорно вмонитор выводила полночь. По моему в примере перепутаны пины. Строку, «iarduino_RTC time
//(RTC_DS1302,6,7,8);» поменял на «iarduino_RTC time (RTC_DS1302,8,6,7);» и все заработало.





#define foto A0 // фоторезистор подключаем к пину А0
#include <AccelStepper.h>// Отличная библиотека, используете его 
#include <Stepper.h>//подходит для тестов и простых задачhttps://xn--18-6kcdusowgbt1a4b.xn--p1ai/%D1%88%D0%B0%D0%B3%D0%BE%D0%B2%D1%8B%D0%B9-%D0%B4%D0%B2%D0%B8%D0%B3%D0%B0%D1%82%D0%B5%D0%BB%D1%8C-%D0%B0%D1%80%D0%B4%D1%83%D0%B8%D0%BD%D0%BE/
#include <iarduino_RTC.h> //http://kip-world.ru/podklyuchenie-chasov-realnogo-vremeni-ds1302-k-arduino.html
const int IN1=2;
const int IN2=3;
const int IN3=4;
const int IN4=5;
int led1 = 13;
int led2 = 12;

const int stepsPerRevolution = 32;//шаги в минуту
Stepper myStepper (stepsPerRevolution, IN1, IN2, IN3, IN4);
iarduino_RTC time(RTC_DS1302,6,7,8);// vcc-5v, gnd-gnd, clk-6, dat-7, rst-8




void setup() {

delay(300);
Serial.begin(9600);
time.begin();
time.settime(0,13,20,2,12,19,1);// 0  сек, 13 мин, 20 час, 2, деакбря, 2019 года, понедельник



{
  myStepper.setSpeed(500);
}



}

void loop() {
if(millis()%1000==0){
  Serial.println(time.gettime("d-m-y, H:i:s, D"));
  delay(1);
  }
  
  int value = analogRead(foto);
  if (value<250)
  {
    myStepper.step(stepsPerRevolution);
    digitalWrite(led1, HIGH);
delay(10000);

  }
 if  (value>250)
myStepper.step(-stepsPerRevolution);
    digitalWrite(led2, HIGH);
delay(10000);


}
