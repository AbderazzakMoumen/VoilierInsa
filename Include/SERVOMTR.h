#ifndef SERVOMTR_H
#define SERVOMTR_H

#include "TIMER.h"
#include "GPIO.h"
#include "GIROUETTE.h"

//Initialiser le servo moteur
void Init_SERVOMTR(void); 

//Calcul du rapport cyclique pour varier l'angle de rotation du servo moteur
float Calcul_DutyCycle_SERVOMTR(float Angle_Vent);

//Commander le servo moteur à l'aide de la PWN
void Commande_SERVOMTR(void);


#endif