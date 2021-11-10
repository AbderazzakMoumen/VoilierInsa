#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"
#include "SERVOMTR.h"
#include "GIROUETTE.h"
#include "PLATEAUMTR.h"

//float theta;

int main(void){

		//Conf_Girouette();
		//Init_SERVOMTR();
		Init_PLATEAUMTR();
		MYUSART_Config();
		MYUSART_IT(4,Commande_PLATEAUMTR();
		while(1)
			{
				//theta = Get_Angle_Girouette();

			}
			return 0;
			
}




