#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"
#include "SERVOMTR.h"
#include "GIROUETTE.h"
#include "PLATEAUMTR.h"
#include "USART.h"
#include "BATTERIE.h"
#include "TELECOMMANDE.h"


float theta;  //Valuer retournée par le capteur incremental indiquante la direction du vent
float Percentage_Batterie; //Valeur qui indique le pourcentage de la batterie restant


void Start(void){

	//Demarrage de la configuration du voilier 
	MYUSART_Config_OUT(); //Configuration USART en OUTPUT
	SEND_INTRODUCTION();  //Envoi introduction à la tablette
	Conf_Girouette();	  //Configuration Girouette
	Init_SERVOMTR();	  //Configuration Servomoteur (Commande voiles) 
	Init_PLATEAUMTR();	  //Configuration Moteur CC   (Commande plateau)
	MYUSART_Config();     //Configuration USART en INPUT
	MYUSART_IT(4,Commande_PLATEAUMTR); //Configuration interruption USART (Commande plateau)
	MyBatterie_Init();    //Configuration de la mesure de la tension de la batterie
	SEND_FIN_CONFIGURATION(); //Envoi fin configuration à la tablette
	Percentage_Batterie = Batterie_Percentage(); //Recupere le pourcentage de batterie restant
	Send_Percentage_Batterie(Percentage_Batterie); //Envoi du pourcentage de batterie restant à la tablette

}


int main(void){

    start();
	while(1)
		{

			theta = Get_Angle_Girouette();
			Commande_SERVOMTR(theta);
			SEND_ALLURE(theta);

		}
		return 0;
			
}



