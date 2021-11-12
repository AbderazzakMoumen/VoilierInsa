#include "SERVOMTR.h"

void Init_SERVOMTR(void){
	// Sortie PWN -> PA8
	//PA8 -> Output Alternate function push-pull

     MyGPIO_Init(GPIOA,8,AltOut_Ppull,OutputMode_10MHz);
     Timer_PWM_Init(TIM1,20000,1);
     Timer_Start(TIM1);
	   

}

float Calcul_DutyCycle_SERVOMTR(float Angle_Vent) {
	//float DC = 95;
	float Duty_Cycle;
	//+Pour un DC de 5% le servo moteur fait un tour de 0° et les voiles ne bougent pas (entre 0° et 45° d'angle avec le vent).
	//+Pour un DC de 7.5% le servo moteur fait un tour de 90° et il faut faire bouger les voiles d'une maniere progressive 
	//jusqu'à atteindre 90° quand le bateau est à 180° du vent(vent arrière), ensuite quand le vent dépasse les 180° avec le bateau le 
	//servo moteur depasse 90° et entraine les voiles vers leur position intiale (vent debout).
	//+Pour un DC de 10% le servo moteur fait un tour de 180° et donc remet les voiles en position initiale(vent debout).
	
	if (Angle_Vent > 360.0 || Angle_Vent < 0.0) {
		Duty_Cycle = 0;
	}
	
	if (Angle_Vent <= 45.0)  {
        Duty_Cycle = 5;
   }
   if (Angle_Vent > 45.0 && Angle_Vent < 70.0) {
		Duty_Cycle = 6; 
	}
	if (Angle_Vent > 70.0 && Angle_Vent < 95.0) {
		Duty_Cycle = 7; 
	}
	if (Angle_Vent > 95.0 && Angle_Vent < 120.0) {
		Duty_Cycle = 8; 
	}
   if (Angle_Vent > 120.0 && Angle_Vent < 145.0) {
		Duty_Cycle = 9; 
	}
	if (Angle_Vent > 145.0 && Angle_Vent < 200.0) {
		Duty_Cycle = 10; 
	}
	if (Angle_Vent > 200.0 && Angle_Vent < 225.0) {
		Duty_Cycle = 9; 
	}
	if (Angle_Vent > 225.0 && Angle_Vent < 250.0) {
		Duty_Cycle = 8; 
	}
   if (Angle_Vent > 250.0 && Angle_Vent < 275.0) {
		Duty_Cycle = 7; 
	}
	if (Angle_Vent > 275.0 && Angle_Vent < 300.0) {
		Duty_Cycle = 6; 
	}
	if (Angle_Vent >= 300.0)  {
        Duty_Cycle = 5;
   }

	
	
	//if (Angle_Vent > 45.0 && Angle_Vent < 140.0) {
	//	Duty_Cycle = 6; 
	//}
	//if (Angle_Vent > 140.0 && Angle_Vent < 200.0) {
	//	Duty_Cycle = 10; 
	//}
	//if (Angle_Vent > 200.0 && Angle_Vent < 260.0) {
	//	Duty_Cycle = 9; 
	//}
	//if (Angle_Vent > 260.0)  {		
    //Duty_Cycle = 10;
   //}




   
	
   //	if (Angle_Vent > 45.0 && Angle_Vent < 315.0) {
   //		Duty_Cycle = (1/80)*Angle_Vent + 5.25; 
   //	}
	
	
	
	
	
   //if (Angle_Vent > 360.0 || Angle_Vent < 0.0) {
   //		//return 100;
   //		Duty_Cycle = 5;
	 //}
	 //if (Angle_Vent <= 45.0 || Angle_Vent >= 315.0)  {		
 	 //DC = 90;
   //Duty_Cycle = 5;
	 //}
   //		if (Angle_Vent > 45.0 && Angle_Vent <= 180.0) {
   //		//DC = 100*(((0.05/135.0)*Angle_Vent)+0.883333333);
   //		Duty_Cycle = (1/80)*Angle_Vent + 5.25; 
   //	}
   //	
   //	if (Angle_Vent > 180.0 && Angle_Vent < 315.0) {
   //		//DC = 100*(((-0.05/135.0)*Angle_Vent)+1.016666667);
   //		Duty_Cycle = (1/80)*Angle_Vent + 5.25;
   //	}
	//return (100 - DC);
	
	
	return (int)Duty_Cycle;
}
void Commande_SERVOMTR(float Angle_girouette) {
	
	 Timer_PWM_DutyCycle_Fix(TIM1, Calcul_DutyCycle_SERVOMTR(Angle_girouette), 1);
}

