#ifndef USART_H
#define USART_H

#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"
#include "math.h"


//Configuration de l'USART en INPUT
void MYUSART_Config(void);


//Initialisation de l'interruption de l'USART
void MYUSART_IT(char Prio,void(*IT_function)(void));


//Mode Reception de l'USART
char MYUSART_RECEIVE(void);


//Configuration de l'USART en OUTPUT
void MYUSART_Config_OUT(void);


//Envoi d'un caractere à la tablette à travers l'USART
void Transm_USART(USART_TypeDef * USART, char caractere);


//Envoi d'un nombre à la tablette
void Send_Number(unsigned int nb);


//Envoi d'une chaine de caractere à la tablette
void Send_Chaine(char * Chaine);



	




#endif

