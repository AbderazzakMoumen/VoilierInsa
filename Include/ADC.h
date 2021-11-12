#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"

//On initialise l'ADC
void MyADC_Init (ADC_TypeDef * ADC);

//On configure l'ADC
void Conf_ADC(ADC_TypeDef * ADC, u8 Channel);

//On recoit la valeur de la conversion
int Valeur_ADC(ADC_TypeDef * ADC);







#endif
