#ifndef SERVOMTR_H
#define SERVOMTR_H

#include "TIMER.h"
#include "GPIO.h"
#include "GIROUETTE.h"


void Init_SERVOMTR(void); 

float Calcul_Pourcentage_Angle(float Angle_Vent);

void Commande_SERVOMTR(void);


#endif