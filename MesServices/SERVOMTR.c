#include "SERVOMTR.h"

void Init_SERVOMTR(){

     MyGPIO_Init(GPIOA,8,AltOut_Ppull,OutputMode_10MHz);
     Timer_PWM_Init(TIM1,20000,1);
     Timer_Start(TIM1);

}

float Calcul_DC_Angle(float Angle_Vent) {
	//float DC = 95;
	int DC = 5;
	//+Pour un DC de 5% le servo moteur fait un tour de 0° et les voiles ne bougent pas (entre 0° et 45° d'angle avec le vent).
	//+Pour un DC de 7.5% le servo moteur fait un tour de 90° et il faut faire bouger les voiles d'une maniere progressive 
	//jusqu'à atteindre 90° quand le bateau est à 180° du vent(vent arrière), ensuite quand le vent dépasse les 180° avec le bateau le 
	//servo moteur depasse 90° et entraine les voiles vers leur position intiale (vent debout).
	//+Pour un DC de 10% le servo moteur fait un tour de 180° et donc remet les voiles en position initiale(vent debout).
	
	if (Angle_Vent > 360.0 || Angle_Vent < 0.0) {
		//return 100;
		DC = 5;
	}
	
	if (Angle_Vent <= 45.0 || Angle_Vent >= 315.0)  {		
		//DC = 90;
		DC = 5;
	}
	
	if (Angle_Vent > 45.0 && Angle_Vent <= 180.0) {
		//DC = 100*(((0.05/135.0)*Angle_Vent)+0.883333333);
		DC = (1/80)*Angle_Vent + 5.25; 
	}
	
	if (Angle_Vent > 180.0 && Angle_Vent < 315.0) {
		//DC = 100*(((-0.05/135.0)*Angle_Vent)+1.016666667);
		DC = (1/80)*Angle_Vent + 5.25;
	}
	//return (100 - DC);
	return DC;
}
void Commande_SERVOMTR(void) {
	 
	 Timer_PWM_DutyCycle_Fix(TIM1, Calcul_DC_Angle(Get_Angle_Girouette()), 1);
}