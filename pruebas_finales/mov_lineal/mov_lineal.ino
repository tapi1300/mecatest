#include <Servo.h>

const int US_Trigger = 2;   //Pin digital 2 para el Trigger del sensor
const int US_Echo = 3;   //Pin digital 3 para el Echo del sensor
const int pin_rueda_DER = 5;
const int pin_rueda_IZQ = 6;
const int IR_IZQ = 11;
const int IR_DER = 10;

long t; //timepo que demora en llegar el eco
long d; //distancia en centimetros

Servo myservoD;
Servo myservoI;


void sendspeed(int speed)
{
  // MAX SPEED      = 10
  // MAX SPEED NEG  = -10
  int max_s = 253;
  int min_s = 1;
  int speed_0 = 100;
  int max = 10;
  int min = -10;

  int vel_izq,vel_der;

  if(speed > 0)
  {
    vel_izq = speed*(max_s-speed_0)/max + speed_0;
    vel_der = speed*(speed_0-min_s)/min + speed_0;
  }
  else if(speed < 0) 
  {
    vel_izq = speed*(speed_0-min_s)/min + speed_0;
    vel_der = speed*(max_s-speed_0)/max + speed_0;
  }
  else {
    vel_izq = speed_0;
    vel_der = speed_0;
  }

  Serial.println(vel_izq);
  Serial.println(" - ");
  Serial.println(vel_der);
  Serial.println("\n");

  analogWrite(pin_rueda_DER,vel_izq);   // DE 1 a 253 con el 100 como 0
  analogWrite(pin_rueda_IZQ,vel_der);   // DE 1 a 253 con el 100 como 0
}







void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //iniciar puerto serie
  myservoD.attach(pin_rueda_DER);
  myservoI.attach(pin_rueda_IZQ);

  pinMode(pin_rueda_DER,OUTPUT);
  pinMode(pin_rueda_IZQ,OUTPUT);
  pinMode(IR_IZQ , INPUT);  //definir pin como entrada
  pinMode(IR_DER , INPUT);  //definir pin como entrada

  pinMode(US_Trigger, OUTPUT); //pin como salida
  pinMode(US_Echo, INPUT);  //pin como entrada
  digitalWrite(US_Trigger, LOW);//Inicializamos el pin con 0

}

void loop() {

  int vel = 1;

  int value_izq = 0;
  int value_der = 0;
  value_izq = digitalRead(IR_IZQ);  //lectura digital de pin
  value_der = digitalRead(IR_DER);  //lectura digital de pin





  digitalWrite(US_Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(US_Trigger, LOW);
  
  t = pulseIn(US_Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //

  int ta = 1;
  if(d < 11)
  {
    ta = 0;
  }

 
  if(value_izq == 0 || value_der == 0)
  {
    myservoD.write(90);  // set servo to mid-point
    myservoI.write(90);  // set servo to mid-point
  }
  else if(value_izq == 1 && value_der == 1)
  {
    if(ta == 0)
    {
      Serial.print("Distancia: ");
      Serial.print(d);      //Enviamos serialmente el valor de la distancia
      Serial.print("cm");
      Serial.println();
      myservoD.write(180);  // set servo to mid-point
      myservoI.write(0);  // set servo to mid-point
    }
    else{
      myservoD.write(110);  // set servo to mid-point
      myservoI.write(70);  // set servo to mid-point
    }
  }
}
