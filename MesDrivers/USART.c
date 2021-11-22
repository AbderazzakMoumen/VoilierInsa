#include "USART.h"
#include "stm32f10x.h"
void (*HandlerUSART1)(void);


/****************   *********   ****************/
/****************   RECEPTION   ****************/
/****************   *********   ****************/


//Configuration de l'USART en INPUT
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


//Initialisation de l'interruption de l'USART
void MYUSART_IT(char Prio,void(*IT_function)(void)){

	USART1->CR1 |= USART_CR1_RXNEIE; // The RXNE bit is set. In other words, data has been received and can be read
	HandlerUSART1 = IT_function;
	NVIC->ISER[1] |= NVIC_ISER_SETENA_5; // NVIC->ISER[1] |= 1<<(37-32);
	NVIC->IP[USART1_IRQn] = (Prio << 4);

}


//Mode Reception de l'USART
char MYUSART_RECEIVE(void){

	return USART1->DR; 
}


//Remise du flag à zèro après Reception
void USART1_IRQHandler (void)
{
	if (HandlerUSART1 != 0){
	(*HandlerUSART1)();
	} 

	USART1->SR &= ~ USART_SR_RXNE; // Flag remise à zero

}




/****************   *********   ****************/
/****************   EMISSION   ****************/
/****************   *********   ****************/



//Configuration de l'USART en OUTPUT
void MYUSART_Config_OUT(void){
	
		// GPIO CONFIGURATION 
		// PA9 USART1_TX
		MyGPIO_Init (GPIOA, 9 , AltOut_Ppull , OutputMode_10MHz) ;
	
	
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // validation horloge USART1
    USART1->CR1 |= USART_CR1_UE; // Activation de l'USART
    USART1->CR1 &= ~USART_CR1_M; // Choix d'une taille de 8 bits de données
    USART1->CR2 &= USART_CR2_STOP; // Choix d'un seul bit de stop
    USART1->BRR |= 468 << 4; // Fixe le baud rate à 9600bps
    USART1->BRR |= 75; // Fixe le baud rate à 9600bps
}


//Envoi d'un caractere à la tablette à travers l'USART
void Transm_USART(USART_TypeDef * USART, char caractere) {
		
	//On active la transmission en mettant el bit TE de USART_CR1 a 1
	USART->CR1 |= (1 << 3);
		
	//Ecriture du caractere a envoyer dans USART_DR
	USART->DR = caractere;
}


//Envoi d'un nombre à la tablette
void Send_Number(unsigned int Number) {

	int a,b,z;

	if(Number == 0){

		Transm_USART(USART1, (char)(((int)'0') + Number));
		//Pour pas remplir le buffer du recepteur
		for (z=0 ; z < 100000 ; z++);

	} else if (Number == 100){

		Transm_USART(USART1, (char)(((int)'0') + 1));
		for (z=0 ; z < 100000 ; z++);

		Transm_USART(USART1, (char)(((int)'0') + 0));
		for (z=0 ; z < 100000 ; z++);

		Transm_USART(USART1, (char)(((int)'0') + 0));
		for (z=0 ; z < 100000 ; z++);

	} else {

		a = floor(Number/10);
		b = Number%10;

		//Envoi de la dizaine
		Transm_USART(USART1, (char)(((int)'0') + a));
		for (z=0 ; z < 100000 ; z++);

		//Envoi de l'unité
		Transm_USART(USART1, (char)(((int)'0') + b));
		for (z=0 ; z < 100000 ; z++);

		}
}



//Envoi d'une chaine de caractere à la tablette
void Send_Chaine(char * Chaine) {
	
	int z;
	char * Caractere;
	Caractere=Chaine;

	while ((*Caractere)!='\0') {

		Transm_USART(USART1, (*Caractere));	
		// Pour pas remplir le buffer du recepteur
		for (z=0 ; z < 100000 ; z++);
		Caractere++;

	}
}








	