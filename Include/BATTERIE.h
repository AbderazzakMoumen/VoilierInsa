#ifndef BATTERIE_H
#define BATTERIE_H

#include "GPIO.h"
#include "ADC.h"

//On configure PC2 en mode analog input et on initialise ADC
void MyBatterie_Init(void);

//On recoit la valeur de la conversion
int Charge_Batterie(void);



#endif
