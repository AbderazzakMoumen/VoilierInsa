#include "BATTERIE.h"

void MyBatterie_Init(void) 
{
	//On configure PC2 en mode analog input
	MyGPIO_Init(GPIOC,2,In_Analog,InputMode);

	//On initialise l'ADC
	MyADC_Init(ADC1);
}

int Charge_Batterie(void) { 
	//On commence la conversion sur Channel 12
	Conf_ADC(ADC1, 12);

	return Valeur_ADC(ADC1);
}