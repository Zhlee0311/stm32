#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t number;

int main()
{
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1, 1, "Num:");
	OLED_ShowString(2, 1, "Cnt:");
	while (1)
	{
		OLED_ShowNum(1, 5, number, 5);
		OLED_ShowNum(2, 5, Timer_GetCounter(),5);
	}
}

void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		number++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
