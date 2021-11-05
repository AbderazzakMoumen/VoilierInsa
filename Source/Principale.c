#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"
#include "SERVOMTR.h"
#include "GIROUETTE.h"

float theta;
int main(void){

		Conf_Girouette();
		while(1)
			{
				theta = Get_Angle_Girouette();
			}
			return 0;
			
}



