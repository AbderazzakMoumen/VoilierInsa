#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"


//Initialisation ADC
void MyADC_Init (ADC_TypeDef * ADC);


//Configuration ADC
void Conf_ADC(ADC_TypeDef * ADC, u8 Channel);


// Valeur retournee par l'ADC
int Valeur_ADC(ADC_TypeDef * ADC);







#endif
