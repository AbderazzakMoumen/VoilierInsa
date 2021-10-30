#include "GIROUETTE.h"


#define PSMAX 0 // Impulsion pour avoir un angle de voile theta maximal
#define PSMIN 90 // Impulsion pour avoir un angle de voile theta minimal


// Configuration broches Codeur sur GPIOA: INDEX->PA5 et CHA->PA6 et CHB->PA7 en INPUT FLOATING
void IncEncoder_GPIO_Config( ){

	MyGPIO_Init (GPIOA, 5 , In_Floating , InputMode ) ;
	MyGPIO_Init (GPIOA, 6 , In_Floating , InputMode ) ;
	MyGPIO_Init (GPIOA, 7 , In_Floating , InputMode ) ;

}

//Mode 3 du Codeur : counting on both TI1 and TI2 edges
void IncEncoder_TIMER_Mode_3(TIM_TypeDef *Timer){
 
	//Encoder interface mode
	// To select Encoder Interface mode write SMS=‘001’ in the TIMx_SMCR register if the 
	// counter is counting on TI2 edges only, SMS=’010’ if it is counting on TI1 edges only and 
	// SMS=’011’ if it is counting on both TI1 and TI2 edges.
	Timer->SMCR &= ~(7 << 0);     // (7 << 0)==(0b111 << 0)
	Timer->SMCR |= (3 << 0);  // (3 << 0)==(0b011 << 0)
	Timer->PSC = 0;
	Timer->ARR = 1440+1;

}


// Configuration TIMER Codeur
void IncEncoder_TIMER_Config( ){

	Timer_Active_Clock (TIM3);  
	IncEncoder_TIMER_Mode_3(TIM3);
	IncEncoder_GPIO_Config( );

}


// Detection de l'angle zero afin de demarrer le Codeur
void IncEncoder_AngleZero(){

	while(MyGPIO_Read(GPIOA,5)==0);

}


// Calcul de Theta
float Calcul_Theta(volatile unsigned int *alpha){
	float theta;
	float aux;
	aux=*alpha * 360.0 / (1440+1);
	if (aux<45 || aux>315){
		theta=0;
	}else{
		if (aux>=45 && aux<=180){
			theta=(2.0/3.0)* aux-30;
		}else{
			if (aux>180 && aux<=315){
			theta=0; // au debut on croyait que theta pouvait varier entre -90 et 90 (2.0/3.0)* *alpha-210;
			}
		}
	}
return theta;
}


// Calcul de l'impulsion pour le servo moteur
float Calcul_Impulsion(float theta){
	return 2 - (theta-PSMAX)/(PSMIN-PSMAX);
}


