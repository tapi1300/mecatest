#include <Servo.h>

const int US_Trigger = 2;
const int US_Echo = 3;
const int pin_rueda_DER = 5;
const int pin_rueda_IZQ = 6;
const int IR_IZQ = 11;
const int IR_DER = 10;

long time_eco;
long dist;
bool parar=false;
int time_init=0;
int sens_detect=0;

Servo myservoD;
Servo myservoI;

#define  NEGRO   0     // Asociamos un color a un número             
#define  BLANCO  1
#define  US_DETECTED 1
// 0 es negro
// 1 es blanco

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  myservoD.attach(pin_rueda_DER);
  myservoI.attach(pin_rueda_IZQ);

  pinMode(pin_rueda_DER,OUTPUT);
  pinMode(pin_rueda_IZQ,OUTPUT);
  pinMode(IR_IZQ , INPUT);
  pinMode(IR_DER , INPUT);

  pinMode(US_Trigger, OUTPUT);
  pinMode(US_Echo, INPUT);
  digitalWrite(US_Trigger, LOW);

}

void loop() {

  int vel = 1;

  int value_izq = 0;
  int value_der = 0;
  value_izq = digitalRead(IR_IZQ);
  value_der = digitalRead(IR_DER);

  digitalWrite(US_Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_Trigger, LOW);
  
  time_eco = pulseIn(US_Echo, HIGH);
  dist = time_eco/59;

  if(dist < 20)
  {
    parar = true;
  }
  else{
    parar = false;
  }

  if(parar)
  {
    // SI HAY OBSTACULO, PARAMOS    
    myservoD.write(90);
    myservoI.write(90);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    // SI HAY COLOR NEGRO EN LOS INFRARROJOS GIRAMOS
    if (value_izq == NEGRO){
      myservoD.write(180);
      myservoI.write(180);
    }
    else if(value_der == NEGRO){
      myservoD.write(0);
      myservoI.write(0);
    }
    // SI NO, NOS MOVEMOS
    else if(value_izq == BLANCO && value_der == BLANCO)
    {
        myservoD.write(180);
        myservoI.write(0);
    }
  }
}
