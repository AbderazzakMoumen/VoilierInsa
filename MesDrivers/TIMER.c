#include "TIMER.h"
void (*pFnc2)(void);

/************************
FONCTIONS GENERALES
************************/

// 	Activation Clock TIMER
void Timer_Active_Clock (TIM_TypeDef *Timer){
	
	if (Timer == TIM1) {
		(RCC->APB2ENR)|= RCC_APB2ENR_TIM1EN; //Clock TIMER1
	}
	else if (Timer == TIM2) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM2EN; //Clock TIMER2
	}
	else if (Timer == TIM3) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM3EN; //Clock TIMER3
	}
	else if (Timer == TIM4) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM4EN; //Clock TIMER4
	}	

}


// Initialisation TIMER (NEW: ARR et PSC automatique pour une durée déterminée)
void Timer_Init(TIM_TypeDef *Timer, float Duree){
	
		int Psc;
		int Arr;
		int Total;
		Timer_Active_Clock(Timer);
		
	  // Calcul de ARR et PSC
		//Total = 72000000*Duree; 
		
		Psc = 35;     
		Arr = ((72 * Duree) / (Psc + 1)-1); 
		
	//	Psc=Psc+1;
		
		Timer->PSC = Psc;
		Timer->ARR = Arr;

}


// Activation de l'interruption TIMER
void Timer_Active_IT( TIM_TypeDef *Timer, char Prio, void (*IT_function) (void) ){


		if( Timer == TIM2){
				NVIC->ISER[0] |= NVIC_ISER_SETENA_28;
				NVIC->IP[28] |= (Prio << 4);
		} else if (Timer == TIM3){
				pFnc2 = IT_function;
				NVIC->ISER[0] |= NVIC_ISER_SETENA_29;
				NVIC->IP[29] |= (Prio << 4);
		}else if(Timer == TIM4){
				NVIC->ISER[0] |= NVIC_ISER_SETENA_30;
				NVIC->IP[30] |= (Prio << 4);
		}
		Timer->DIER |= TIM_DIER_UIE;

}


// Handler TIMER2
void TIM2_IRQHandler(void) { 
	
	if (pFnc2 != 0){
		(*pFnc2)();
	} 
	TIM2->SR &= ~TIM_SR_UIF;
}


// Handler TIMER3
void TIM3_IRQHandler(void) { 
	
	if (pFnc2 != 0){
		(*pFnc2)();
	} 
	TIM3->SR &= ~TIM_SR_UIF;
}


// Handler TIMER4
void TIM4_IRQHandler(void) { 
	
	if (pFnc2 != 0){
		(*pFnc2)();
	} 
	TIM4->SR &= ~TIM_SR_UIF;
}

/************************
           PWM
************************/


//	Initialisation PWM du Timer
void Timer_PWM_Init(TIM_TypeDef *Timer, float Duree, int Channel){
	//int Duree = (1000/(Frequence_PWM_kHz)); // Duree en micro secondes 
 	Timer_Init(Timer, Duree);
	switch (Channel) {
		
			 case 1:
			 	// On utilise le PWM en mode 1 
			  Timer->CCMR1 &= ~(6 << 4);
			  Timer->CCMR1 |= (6 << 4);
				Timer->CCER &= ~(0 << 0);
				Timer->CCER |= (1 << 0);
		    //Initialisation de la PWM d'un Duty Cycle de 0%
				Timer->CCR1=0;
				break;
			 
			 case 2:
				 
			  Timer->CCMR1 &= ~(6 << 12);
			  Timer->CCMR1 |= (6 << 12);
				Timer->CCER &= ~(0 << 4);
				Timer->CCER |= (1 << 4);
		    
				Timer->CCR2=0;
				break;
			 
			 case 3:

			  Timer->CCMR2 &= ~(6 << 4);
			  Timer->CCMR2 |= (6 << 4);
				Timer->CCER &= ~(0 << 8);
				Timer->CCER |= (1 << 8);

				Timer->CCR3=0;
				break;
			 
			 case 4:

			  Timer->CCMR2 &= ~(6 << 12);
			  Timer->CCMR2 |= (6 << 12);
				Timer->CCER &= ~(0 << 12);
				Timer->CCER |= (1 << 12);

				Timer->CCR4=0;
				break;
			 
			 default:

				 break;
		 
 }
}


//	 Fixer la le rapport cyclique de la PWM 
void Timer_PWM_DutyCycle_Fix(TIM_TypeDef *Timer, int Duty_Cycle, int Channel){
     int Arr;
     if ((Duty_Cycle <= 100) && (Duty_Cycle >= 0)) {
			 
       Arr = Timer->ARR;
			 
			 switch (Channel) {
				 case 1:
                     Timer->CCR1 = (Arr*Duty_Cycle)/100;
				     break;

				 case 2:
                     Timer->CCR2 = (Arr*Duty_Cycle)/100;
				     break;

				 case 3:
                     Timer->CCR3 = (Arr*Duty_Cycle)/100;
				     break;

				 case 4:
                     Timer->CCR4 = (Arr*Duty_Cycle)/100;
				     break;
			 }
     }
 }




