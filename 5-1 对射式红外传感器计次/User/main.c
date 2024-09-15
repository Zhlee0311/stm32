#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

int main()
{
	OLED_Init();
	CounterSensor_Init();

	OLED_ShowString(1, 1, "Count:"); 

	while (1)
	{
		OLED_ShowNum(1, 7, CounterSensor_Get(), 3);
	}
}
