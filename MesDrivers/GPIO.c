#include "GPIO.h"
#include "stm32f10x.h"


// GPIO Initialisation et choix de la Config et Mode
void MyGPIO_Init (GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf, char GPIO_Mode )
{
	// 	Clock Activation 
	if (GPIO == GPIOA) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPAEN;
	}
	else if (GPIO == GPIOB) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPBEN;
	}
	else if (GPIO == GPIOC) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPCEN;
	}
	else if (GPIO == GPIOD) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPDEN;
	}


	// 	Initialisation du GPIO
	if ( GPIO_Pin < 8 ) { 
				GPIO -> CRL &= ~(0xF << (GPIO_Pin *4));
				GPIO -> CRL |= (GPIO_Mode << (GPIO_Pin *4))| (GPIO_Conf << ((GPIO_Pin *4)+2));
	}
	  else if ( GPIO_Pin >= 8 ) {
				GPIO -> CRH &= ~(0xF << ((GPIO_Pin-8) *4));
				GPIO -> CRH |= (GPIO_Mode << ((GPIO_Pin-8) *4))| (GPIO_Conf << (((GPIO_Pin-8) *4)+2));
	}
		
}


// Lire la broche : renvoie 0 ou autre chose different de 0
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	
	int Lecture;
	Lecture = (GPIO -> IDR & (0x1 << GPIO_Pin)) >> GPIO_Pin;
	return Lecture;

}


// Mettre la broche à 1
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {

			GPIO->ODR |= (1 << GPIO_Pin);

}


// Mettre la broche à 0
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ){

		GPIO->ODR &= ~(1 << GPIO_Pin);

}


// Faire clignotter la borche 
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ){

		if ( (GPIO->ODR & (1 << GPIO_Pin)) == (1<<GPIO_Pin))
			MyGPIO_Reset (GPIO , GPIO_Pin ) ;
		else
			MyGPIO_Set (GPIO , GPIO_Pin ) ;
		
}



