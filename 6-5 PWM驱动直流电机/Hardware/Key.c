#include "stm32f10x.h" // Device header
#include "Delay.h"

void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief 读取按键编号
 */
uint8_t Key_GetNum(void)
{
    // 为防止抖动特意加了500ms延时
    uint8_t KeyNum = 0;
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==Bit_RESET){
		Delay_ms(500);
        while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==Bit_RESET);
		Delay_ms(500);
        KeyNum = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==Bit_RESET){
		Delay_ms(20);
        while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==Bit_RESET);
        Delay_ms(20);
		KeyNum = 2;
    }
    return KeyNum;
}
