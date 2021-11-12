#include "ADC.h"
#include "stm32f10x.h"

void MyADC_Init (ADC_TypeDef * ADC) 
{
    
	if (ADC == ADC1) {
		(RCC->APB2ENR)|= RCC_APB2ENR_ADC1EN;
		//On divise par 6 la fréquence d'entrée (72MHz / 6 = 12MHz) car ADC doit avoir une fréquence < 14MHz pour que le périphérique fonctionne.
	    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

		// On active ADC1 
		ADC1->CR2 |= (0x01 << 0);
	}
	if (ADC == ADC2) {
		(RCC->APB2ENR)|= RCC_APB2ENR_ADC2EN;
		//On divise par 6 la fréquence d'entrée (72MHz / 6 = 12MHz) car ADC doit avoir une fréquence < 14MHz pour que le périphérique fonctionne.
	    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
		
		// On a active ADC2
		ADC2->CR2 |= (0x01 << 0);
	}
	if (nb_cycles == 7.5){	
		// 001: 7.5 cycles
		while (champ < 10) {
			ADC->SMPR1 |= (0x01 << num_bit);
			ADC->SMPR2 |= (0x01 << num_bit);
			champ++;
			num_bit += 3;
		}
	}
	
}

void Conf_ADC(ADC_TypeDef * ADC, u8 Channel) 
{
    // Init EOC register (on le met à 0)
	ADC->SR &= ~(0x01 << 1);

    //On souhaite faire une seule conversion
    ADC->SQR1 &= ADC_SQR1_L; 

    //On choisit quelle voie on souhaite convertir
    ADC->SQR3 |= Channel;

}

int Valeur_ADC(ADC_TypeDef * ADC) 
{
	//On lance la conversion
    ADC->CR2 |= (0x01 << 0); 
    
    //On attend que le End Of Conversion passe à 1 (ce qui veut dire que la conversion est finie :) )
    while ((ADC->SR & (0x01 << 1)) == 0);
	
	return (ADC->DR);
}
