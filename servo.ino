#include <Servo.h>

//Definiendo Servos
Servo servohori; //Servo horizontal
int servoh = 100; 
int servohLimitHigh = 160; //Valor maximo de movimiento de 160
int servohLimitLow = 20; //Valor minimod de movimiento de 20

Servo servoverti; //Servo vertical
int servov = 100; 
int servovLimitHigh = 160; //Valor maximo de movimiento de 160
int servovLimitLow = 20; //Valor minimod de movimiento de 20

//Asignacion de variables LDR
int ldrsup_i = 2; //LDR superior izquierdo
int ldrsup_d = 1; //LDR superior derecho
int ldrinf_i = 3; //LDR inferior izquierdo
int ldrinf_d = 0; //LDR inferior derecho

void setup () //Parte que se ejecutara una sola vez
{
  servohori.attach(10);
  servohori.write(100); //Ubica al servo horizontal en la posicion 100
  servoverti.attach(9);
  servoverti.write(100); //Ubica al servo vertical en la posicion 100
  delay(500); //Retraso o delay de 500 milisegundos
}

void loop() //Parte que se repetira constantemente
{
  servoh = servohori.read(); //Lee los valores actuales del servo horizontal
  servov = servoverti.read(); //Lee los valore actuales del servo vertical
  //Asignando valores analogicos de cada LDR
  int sup_i = analogRead(ldrsup_i); //Valor del LDR superior izquierdo
  int sup_d = analogRead(ldrsup_d); //Valor del LDR superior derecho
  int inf_i = analogRead(ldrinf_i); //Valor del LDR inferior izquierdo
  int inf_d = analogRead(ldrinf_d); //Valor del LDR inferior derecho

  // calculando el Promedio de los LDRs

  int promsup = (sup_i + sup_d) / 2; //Promedio de los LDRs superiores
  int prominf = (inf_i + inf_d) / 2; //Promedio de los LDRs inferiores
  int prom_i = (sup_i + inf_i) / 2; //Promedio de los LDRs izquierdos
  int prom_d = (sup_d + inf_d) / 2; //Promedio de los LDRs derechos

  //Condicion para el movimiento de los servos

  /*Si el promedio de los LDRs superiores es menor al de los LDRs inferiores
  el servo vertical se movera hacia arriba*/
  if (promsup < prominf)
  {
    servoverti.write(servov +1);

    //Condicion que evita que el servo se pase del valor limite
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(50); //Retraso o delay de 10 milisegundos
  }
  /*Si el promedio de los LDRs superiores es mayor al de los LDRs inferiores
  el servo vertical se movera hacia abajo*/
  else if (prominf < promsup)
  {
    servoverti.write(servov -1);
    
    //Condicion que evita que el servo se pase del valor limite
    if (servov < servovLimitLow)
    {
      servov = servovLimitLow;
    }
    delay(50); //Retraso o delay de 10 milisegundos
  }
  //De otro modo, se mantendra en el mismo valor
  else 
  {
    servoverti.write(servov);
  }
  /*Si el promedio de los LDRs izquierdos es mayor al de los LDRs derechos
  el servo horizontal se movera hacia la derecha*/
  if (prom_i > prom_d)
  {
    servohori.write(servoh +1);
    //Condicion que evita que el servo pase del valor limite
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(50); //Retraso o delay de 10 milisegundos
  }
  /*Si el promedio de los LDRs derechos es mayor al de los LDRs izquierdos
  el servo horizontal se movera hacia la izquierda*/
  else if (prom_d > prom_i)
  {
    servohori.write(servoh -1);
    //Condicion que evita que el servo pase del valor limite
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    delay(50); //Retraso o delay de 10 milisegundos
  }
  //De otro modo, se mantendra en el mismo valor
  else 
  {
    servohori.write(servoh);
  }
  delay(100); //Retraso o delay de 50 milisegundos
}