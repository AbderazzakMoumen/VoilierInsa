#ifndef USART_H
#define USART_H

#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"

void MYUSART_Config(void);
void MYUSART_IT(char Prio,void(*IT_function)(void));
char MYUSART_RECEIVE(void);






#endif

