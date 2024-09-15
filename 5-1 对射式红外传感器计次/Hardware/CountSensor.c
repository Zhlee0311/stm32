#include "stm32f10x.h" // Device header
#include "Delay.h"

uint16_t CounterSensor_Count;

void CounterSensor_Init(void)
{
    // 配置GPIOB端口时钟、AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 配置GPIOB_Pin_14
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 配置AFIO多路选择，选择GPIOB_Pin_14作为EXTI_Line14的输入源
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

    // 配置EXTI_Line14（中断线、中断的模式、触发方式等配置）
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 配置NVIC（中断通道、响应优先级和抢占优先级等配置）
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 优先组2，其中抢占优先级和响应优先级各占2位
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; // EXTI15_10_IRQn 是一个枚举值，用于标识外部中断线15到10的中断请求
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}

uint16_t CounterSensor_Get(void)
{
    return CounterSensor_Count;
}

// 中断服务函数
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line14) == SET)
    {

        if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_14) == SET)
        {
            Delay_ms(200);
            CounterSensor_Count++;
        }
        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
}
