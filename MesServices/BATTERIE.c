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

void Send_Perc_Tension_Batterie(void) {
	char PercBatterie[]="\n\rPerc batterie restant: ";
	// Cahier des charges pour l'alimentation
	const float Alim = 12.0;
	const float Pont_Diviseur = 1./13.;
	const float Resolution_ADC = 4096./3.3;
	// Calcul de tension de la batterie en percentage
	float Tension_Batterie = (float)(Get_Batterie_Charge());
	float Tension_Max = (float)(Alim * Pont_Diviseur * Resolution_ADC);
	unsigned int Percentage_Restant = (unsigned int)(Tension_Batterie/Tension_Max * 100.0);
	
	Send_Chaine(PercBatterie);
	Send_Number(Percentage_Restant);
}
