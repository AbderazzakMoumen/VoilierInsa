#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"
#include "SERVOMTR.h"
#include "GIROUETTE.h"

//float theta;
int Direction;
float Duty_cycle;
int main(void){

		Conf_Girouette();
		Init_PLATEAUMTR(void);
		while(1)
			{
				//theta = Get_Angle_Girouette();
				Commande_PLATEAUMTR(Direction, Duty_cycle);

			}
			return 0;
			
}



