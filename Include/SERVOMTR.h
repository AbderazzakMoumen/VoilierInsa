#ifndef SERVOMTR_H
#define SERVOMTR_H

#include "TIMER.h"
#include "GPIO.h"
#include "GIROUETTE.h"


//Initialisation du Servomoteur
void Init_SERVOMTR(void); 


//Calcul du rapport cyclique pour varier l'angle de rotation du servo moteur
float Calcul_DutyCycle_SERVOMTR(float Angle_Vent);


//Commande du Servomoteur à l'aide de la PWN
void Commande_SERVOMTR(float Angle_girouette);


#endif

