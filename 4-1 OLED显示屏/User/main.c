#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"

int main()
{
	OLED_Init();

	OLED_ShowChar(1, 1, 'A'); // 显示字符'A'

	OLED_ShowString(1, 3, "I love Apple"); // 显示字符串"Hello World!"

	OLED_ShowNum(2, 1, 12345, 5); // 显示数字12345

	OLED_ShowSignedNum(2, 7, 12345, 5); // 显示有符号数字+12345

	OLED_ShowHexNum(3, 1, 0xAA55, 4); // 显示十六进制数0xAA55

	OLED_ShowBinNum(4, 1, 0xAA55, 16); // 显示二进制数0b1010101001010101

	while (1)
	{
	}
}
