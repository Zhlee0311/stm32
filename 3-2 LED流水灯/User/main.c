#include "stm32f10x.h" // Device header
#include "Delay.h"

int main()
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	while (1)
	{
		GPIO_Write(GPIOA, ~0x0001); // 0000_0000_0000_0001
		Delay_ms(50);
		GPIO_Write(GPIOA, ~0x0002); // 0000_0000_0000_0010
		Delay_ms(50);
		GPIO_Write(GPIOA, ~0x0004); // 0000_0000_0000_0100
		Delay_ms(50);
		GPIO_Write(GPIOA, ~0x0008); // 0000_0000_0000_1000
		Delay_ms(50);
		GPIO_Write(GPIOA, ~0x0010); // 0000_0000_0001_0000
		Delay_ms(50);
		GPIO_Write(GPIOA, ~0x0020); // 0000_0000_0010_0000
		Delay_ms(50);
		GPIO_Write(GPIOA, ~0x0040); // 0000_0000_0100_0000
		Delay_ms(50);
		GPIO_Write(GPIOA, ~0x0080); // 0000_0000_1000_0000
		Delay_ms(50);
	}
}
