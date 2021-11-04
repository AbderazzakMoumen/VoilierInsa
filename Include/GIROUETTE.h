#ifndef GIROUETTE_H
#define GIROUETTE_H

#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"

// Configuration broches GPIOA, INDEX->PA5 et CHA->PA6 et CHB->PA7 en INPUT FLOATING
void IncEncoder_GPIO_Config(void); 


//Mode 3 du Codeur : counting on both TI1 and TI2 edges
void IncEncoder_TIMER_Mode_3(TIM_TypeDef *Timer);


// Configuration TIMER Codeur
void IncEncoder_TIMER_Config(void);


// Detection de l'angle zero afin de demarrer le Codeur
void IncEncoder_AngleZero(void);


// Configuration Girouette 
void Conf_Girouette(void);


// 	Retourner l'angle de la Girouette
float Get_Angle_Girouette(void);


#endif