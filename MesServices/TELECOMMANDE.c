#include "TELECOMMANDE.h"


//Envoi du pourcentage de la batterie restante à la tablette
void Send_Percentage_Batterie(unsigned int Percentage_Batterie ){

	char MESSAGE0[]="\n";
	char MESSAGE1[]="Batterie :  ";
	char MESSAGE2[]=" %\n";
	
	if (Percentage_Batterie > 100 ){		

		//Envoi d'un message d'erreur
		char MES1[]="ERROR";
		Send_Chaine(MES1);

	} else {

		//Envoi du pourcentage de la batterie
		Send_Chaine(MESSAGE0);
		Send_Chaine(MESSAGE1);
		Send_Number(Percentage_Batterie);
		Send_Chaine(MESSAGE2);	

	}	
}


//Envoi de l'introduction de la configuration à la tablette
void SEND_INTRODUCTION(void){

	char MES0[]="*********************************\n";
	char MES1[]="\n";
	char MES2[]="CONFIGURATION VOILIER EN COURS\n";
	char MES3[]="\n";
	char MES4[]="TOURNEZ GIROUETTE POUR AVANCER\n";
	
	Send_Chaine(MES0);
	Send_Chaine(MES1);
	Send_Chaine(MES2);
	Send_Chaine(MES3);
	Send_Chaine(MES4);	
	
}


//Envoi de la fin de la configuration à la tablette
void SEND_FIN_CONFIGURATION(void){
	

	char MESSA1[]="\n";
	char MESSA2[]="ANGLE ZERO DETECTE  \n";
	char MESSA3[]="\n";
	char MESSA4[]="CONFIGURATION TERMINE \n\r";
	char MESSA5[]="**********************\n";

	
	Send_Chaine(MESSA1);
	Send_Chaine(MESSA2);
	Send_Chaine(MESSA3);
	Send_Chaine(MESSA4);
	Send_Chaine(MESSA5);
	
}


//Envoi de l'allure en temps réel du Voilier
void SEND_ALLURE(float theta){

	if ((0<=theta && theta<40) || (theta >=320) )
	    {
				
		char MESS1[]="Le voilier navigue au Vent Debut\n";
		Send_Chaine(MESS1);
		
		}
	else if ((40<= theta && theta<50) || (theta>=310 &&  theta < 320)) {
			char MESS2[]="Le voilier navigue au Pres\n";
			Send_Chaine(MESS2);
		}
	else if ((50<= theta &&  theta<65) || (theta >= 295 && theta < 310))
		 {
			char MESS3[]="Le voilier navigue au Bon Plein\n";
			Send_Chaine(MESS3);

		 }
	else if ((65<= theta && theta<90) || (theta>270 && theta <= 295))
		{
			char MESS4[]="Le voilier navigue au Petit Largue\n";
			Send_Chaine(MESS4);
		}
    else if ((90 == theta) || (theta ==270))
		{
			char MESS5[]="Le voilier navigue au Travers\n";
			Send_Chaine(MESS5);
		}
	else if ((90 < theta && theta < 115) || (theta >= 245 && theta < 270))
		{
			char MESS6[]="Le voilier navigue au Largue\n";
			Send_Chaine(MESS6);
		}
	else if ((115 <= theta && theta < 155) || (theta >= 205 && theta < 245))
		{
			char MESS7[]="Le voilier navigue au Grand Largue\n";
			Send_Chaine(MESS7);
		}
	else if ((theta <= 205) && (theta >= 155))
		{
			char MESS8[]="Le voilier navigue au Vent Arriere\n";
			Send_Chaine(MESS8);
		}
	else
		{
			char MESS9[]="Le voilier navigue au Vent Arriere\n";
			Send_Chaine(MESS9);
		}

		delay(100);

}


//Envoi allerte batterie faible
void SEND_ALLERTE(float Perce){

     if (Perce< 50){
			 
					char MESS10[]="ALLERTE: Le niveau de batterie est faible !\n";
					Send_Chaine(MESS10);
			 
     }
}


////Fonction de Delay
void delay(uint16_t delay)
{
  volatile unsigned int num;
  for (num = 0; num < delay; num++)
  {
			volatile unsigned int num;
			volatile unsigned int t;

			for (num = 0; num < 1000; num++)
			{
				t = 11;
				while (t != 0)
				{
					t--;
				}
			}
  }
}
