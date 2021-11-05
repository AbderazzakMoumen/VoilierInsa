#include "SERVOMTR.h"

void Initialisation_SERVOMTR(){
Timer_PWM_Init(TIM4,0.02,3);
MyGPIO_Init(GPIOB,8,AltOut_Ppull,OutputMode_2MHz);
}
void Configuration_SERVOMTR(){
	
	
}
