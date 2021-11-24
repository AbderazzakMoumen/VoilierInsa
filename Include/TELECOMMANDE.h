#ifndef TELECOMMANDE_H
#define TELECOMMANDE_H

#include "USART.h"

//Envoi du pourcentage de la batterie restante à la tablette
void Send_Percentage_Batterie(unsigned int Percentage_Batterie );


//Envoi de l'introduction de la configuration à la tablette
void SEND_INTRODUCTION(void);


//Envoi de la fin de la configuration à la tablette
void SEND_FIN_CONFIGURATION(void);


//Envoi de l'allure en temps réel du Voilier
void SEND_ALLURE(float Perce);

//Envoi allerte batterie faible
void SEND_ALLERTE(float Perce);

////Fonction de Delay
//void delay(int a);

void delay_ms(uint16_t delay_ms);



#endif

