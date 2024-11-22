#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

int main()
{
	OLED_Init();

	Serial_Init();
	// Serial_SendByte('A');

	// uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
	// Serial_SendArray(MyArray, 4);
	// Serial_SendString("Hello,World!\r\n");

	// Serial_SendNumber(12345, 5);
	Serial_Printf("你好世界\r\n");
	while (1)
	{
	}
}
