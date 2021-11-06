#include "SERVOMTR.h"

void Init_SERVOMTR(){

     MyGPIO_Init(GPIOA,8,AltOut_Ppull,OutputMode_10MHz);
     Timer_PWM_Init(TIM1,20000,1);
     Timer_Start(TIM1);

}

float Calcul_Pourcentage_Angle(float Angle_Vent) {
	float Pourcentage = 0.95;
	
	if (Angle_Vent > 360.0 || Angle_Vent < 0.0) {
		return 1.00;
	}
	
	if (Angle_Vent <= 45.0 || Angle_Vent >= 315.0)  {		
		Pourcentage = 0.90;
	}
	
	if (Angle_Vent > 45.0 && Angle_Vent <= 180.0) {
		Pourcentage = ((0.05/135.0)*Angle_Vent)+0.883333333;
	}
	
	if (Angle_Vent > 180.0 && Angle_Vent < 315.0) {
		Pourcentage = ((-0.05/135.0)*Angle_Vent)+1.016666667;
	}
	
	return (1 - Pourcentage);
}
void Commande_SERVOMTR(void) {
	 
	 Timer_PWM_DutyCycle_Fix(TIM1, Calcul_Pourcentage_Angle(Get_Angle_Girouette()), 1);
}