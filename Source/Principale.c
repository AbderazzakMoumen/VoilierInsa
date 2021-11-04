#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"
#include "SERVOMTR.h"
#include "GIROUETTE.h"


int main(void){

		Conf_Girouette();
		while(1)
			{
				float theta;
				theta = Get_Angle_Girouette();
			}
			return 0;
			
}



