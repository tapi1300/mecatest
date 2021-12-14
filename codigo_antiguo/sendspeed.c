#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define min(a,b) fmin(a,b)
#define max(a,b) fmax(a,b)

void sendspeed(int speed)
{
  // MAX SPEED      = 10
  // MAX SPEED NEG  = -10
  int speed_0 = 90;
  int max_arg = 10;
  int min_arg = -10;

  speed = min(speed,max_arg);
  speed = max(speed,min_arg);

  int vel_izq,vel_der;

  if(speed > 0)
  {
    vel_izq = speed*speed_0/max_arg + speed_0;
    vel_der = speed*speed_0/min_arg + speed_0;
  }
  else if(speed < 0) 
  {
    vel_izq = speed*speed_0/min_arg + speed_0;
    vel_der = speed*speed_0/max_arg + speed_0;
  }
  else {
    vel_izq = speed_0;
    vel_der = speed_0;
  }

  printf("%d - %d\n", vel_izq, vel_der);

//   analogWrite(pin_rueda_DER,vel_izq);   // DE 1 a 253 con el 100 como 0
//   analogWrite(pin_rueda_IZQ,vel_der);   // DE 1 a 253 con el 100 como 0
}


int main()
{
    sendspeed(3);
}