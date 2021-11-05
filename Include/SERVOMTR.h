#ifndef SERVOMTR_H
#define SERVOMTR_H

#include "TIMER.h"
#include "GPIO.h"
#include "GIROUETTE.h"


void Init_SERVOMTR(void); 

float Calcule_Percentage_Angle(float Angle_Vent);

void Commander_Voiles(void);


#endif