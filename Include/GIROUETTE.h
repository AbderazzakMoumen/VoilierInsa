#ifndef GIROUETTE_H
#define GIROUETTE_H

#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"

// Configuration broches GPIOA, INDEX->PA5 et CHA->PA6 et CHB->PA7 en INPUT FLOATING
void IncEncoder_GPIO_Config( ); 


// Configuration TIMER Codeur
void IncEncoder_TIMER_Config( );


//Mode 3 du Codeur : counting on both TI1 and TI2 edges
void IncEncoder_TIMER_Mode_3(TIM_TypeDef *Timer);


// Detection de l'angle zero afin de demarrer le Codeur
void IncEncoder_AngleZero();


// Calcul de Theta
// Theta : Angle pour le quel les voiles doivent se déplacer
// Alpha : Angledu vent returné avec Timer->CNT (0° à 360°)
float Calcul_Theta(volatile unsigned int *alpha);


// Calcul de l'impulsion pour le servo moteur à partir de l'angle theta
// Les voiles doivent se deplacer de -90° à 90°
// On return le Duty Cycle necessaire pour la PWM
float Calcul_Impulsion(float theta);




#endif