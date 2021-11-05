#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"
#include "SERVOMTR.h"
#include "GIROUETTE.h"
#include "PLATEAUMTR.h"

//float theta;
int Direction;
float Duty_cycle;
int main(void){

		//Conf_Girouette();
		//Init_SERVOMTR();
		Init_PLATEAUMTR();
		while(1)
			{
				//theta = Get_Angle_Girouette();
				Commande_PLATEAUMTR(Direction, Duty_cycle);

			}
			return 0;
			
}



