#include "PLATEAUMTR.h"

// Initialisation Moteur Plateau
void Init_PLATEAUMTR(void) {
	
	// Configuration broches Moteur Plateau sur GPIOA: Plateau PWM -> PA1 et Plateau Dir. -> PA4 
	// PA1= TIM2_CH2 
	// PA1 -> Output Alternate function push-pull
	// PA4 -> Output Open-drain
	MyGPIO_Init (GPIOA, 1 , AltOut_Ppull , OutputMode_10MHz) ;
	MyGPIO_Init (GPIOA, 4 , Out_Ppull , OutputMode_10MHz) ;

 
	// Le signal PWM est de fréquence 20kHz donc la durée est de 50 us
	Timer_PWM_Init(TIM2, 50, 2);
	Timer_Start(TIM2);
}


// Commande du Moteur Plateau
void Commande_PLATEAUMTR(int Direction, float Duty_cycle) {

	if (Direction == 0){
		// Moteur Plateau tourne à gauche
		 MyGPIO_Reset(GPIOA, 4);
		 }
	if (Direction == 1){
		// Moteur Plateau tourne à droite
		 MyGPIO_Set(GPIOA, 4);
		 } 

	// Vitesse de rotation du Moteur Plateau
	Timer_PWM_DutyCycle_Fix(TIM2, Duty_cycle, 2);

}
