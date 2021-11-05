#include "SERVOMTR.h"

void Init_SERVOMTR(){

     MyGPIO_Init(GPIOA,8,AltOut_Ppull,OutputMode_10MHz);
     Timer_PWM_Init(TIM1,20000,1);

}

float Calcule_Percentage_Angle(float Angle_Vent) {
	float Perc = 0.95;
	
	if (Angle_Vent > 360.0 || Angle_Vent < 0.0) {
		return 1.00;
	}
	
	if (Angle_Vent <= 45.0 || Angle_Vent >= 315.0)  {		
		Perc = 0.90;
	}
	
	if (Angle_Vent > 45.0 && Angle_Vent <= 180.0) {
		Perc = ((0.05/135.0)*Angle_Vent)+0.883333333;
	}
	
	if (Angle_Vent > 180.0 && Angle_Vent < 315.0) {
		Perc = ((-0.05/135.0)*Angle_Vent)+1.016666667;
	}
	
	return (1 - Perc);
}
void Commander_Voiles(void) {
	 
	 Timer_PWM_DutyCycle_Fix(TIM1, Calcule_Percentage_Angle(Get_Angle_Girouette()), 1);
}