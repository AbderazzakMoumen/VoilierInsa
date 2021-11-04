#include "GIROUETTE.h"
#include "stm32f10x.h"




// Configuration broches Codeur sur GPIOA: INDEX->PA5 et CHA->PA6 et CHB->PA7 en INPUT FLOATING
// PA6= TIM3_CH1 et PA7=TIM3_CH2
void IncEncoder_GPIO_Config(){

	MyGPIO_Init (GPIOA, 5 , In_Floating , InputMode ) ;
	MyGPIO_Init (GPIOA, 6 , In_Floating , InputMode ) ;
	MyGPIO_Init (GPIOA, 7 , In_Floating , InputMode ) ;

}

//Mode 3 du Codeur : counting on both TI1 and TI2 edges
void IncEncoder_TIMER_Mode_3(TIM_TypeDef *Timer){
 
 	Timer_Active_Clock (Timer);
	//Encoder interface mode
	// To select Encoder Interface mode write SMS=‘001’ in the TIMx_SMCR register if the 
	// counter is counting on TI2 edges only, SMS=’010’ if it is counting on TI1 edges only and 
	// SMS=’011’ if it is counting on both TI1 and TI2 edges.
	Timer->SMCR &= ~(7 << 0);     // (7 << 0)==(0b111 << 0)
	Timer->SMCR |= (3 << 0);  // (3 << 0)==(0b011 << 0)
	Timer->PSC = 0;
	Timer->ARR = 720; //1 tour == 360 périodes sur chaque voie

}


// Configuration TIMER Codeur
void IncEncoder_TIMER_Config(){

	IncEncoder_GPIO_Config();  
	IncEncoder_TIMER_Mode_3(TIM3);

	//Configuration Interruption EXTI PA5
	(EXTI->IMR) = 0x01<<5 ;
	// Activation Interruption EXTI sur front montant PA5
	(EXTI->RTSR)|=(0x01<<5); 
	// Désactivation Interruption EXTI sur front descendant PA5  
	(EXTI->FTSR) &= ~(0x01 <<5);

	// Activation Interruption EXTI au niveau du coeur
	// L’interruption EXTI au niveau du coeur est identifiée par le numéro 23
	NVIC->ISER[0] = NVIC->ISER[0] | (1 << 23);
	
	// Priorité Interruption EXTI
	NVIC->IP[23]=4;

}


// Detection de l'angle zero afin de demarrer le Codeur
void IncEncoder_AngleZero(){

	while (MyGPIO_Read(GPIOA,5) == 0);

	Timer_Start(TIM3);

}


// Configuration Girouette 
void Conf_Girouette(){

	// Configuration TIMER Codeur
	IncEncoder_TIMER_Config();

	// Detection de l'angle zero afin de demarrer le Codeur
	IncEncoder_AngleZero();

}

// 	Retourner l'angle de la Girouette
float Get_Angle_Girouette(){
	float Angle_girouette;
	Angle_girouette = (float)TIM3->CNT;
	Angle_girouette = angle_girouette / 2;
	return Angle_girouette;
}


// Handler EXTI
void EXTI9_5_IRQHandler() {

	// Remise à zéro du compteur  
	TIM3->CNT=0x0; 

	// Remise à zéro du flag 
	EXTI->PR |= 0x1 <<5;
}
