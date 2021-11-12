#include "USART.h"
#include "stm32f10x.h"

void (*HandlerUSART1)(void);

void MYUSART_Config(void) {

	// GPIO CONFIGURATION 
	// PA10 USART1_RX / TIM1_CH3
	MyGPIO_Init (GPIOA, 10 , In_PullUp , InputMode) ;

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //Enable the USART by writing the UE bit in USART_CR1 register to 1.
    USART1->CR1 |= USART_CR1_UE; // USART Activation 
    USART1->CR1 &= ~USART_CR1_M; // Program the M bit in USART_CR1 to define the word length 8 bits

    USART1->BRR |= 468 << 4; // Fixe le baud rate à 9600bps
    USART1->BRR |= 75; // Fixe le baud rate à 9600bps
    USART1->CR1 |= USART_CR1_RE; // Set the RE bit USART_CR1. RECEIVER MODE ENABLE
}


void MYUSART_IT(char Prio,void(*IT_function)(void)){

	USART1->CR1 |= USART_CR1_RXNEIE; // The RXNE bit is set. In other words, data has been received and can be read
	HandlerUSART1 = IT_function;
	NVIC->ISER[1] |= NVIC_ISER_SETENA_5; // NVIC->ISER[1] |= 1<<(37-32);
	NVIC->IP[USART1_IRQn] = (Prio << 4);

}

char MYUSART_RECEIVE(void){

	return USART1->DR; 
}


void USART1_IRQHandler (void)
{
	if (HandlerUSART1 != 0){
	(*HandlerUSART1)();
	} 

	USART1->SR &= ~ USART_SR_RXNE; // Flag remise à zero

}

