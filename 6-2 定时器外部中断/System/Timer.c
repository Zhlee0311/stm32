#include "stm32f10x.h" // Device header


void Timer_Init()
{
    // 外设时钟使能
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // TIM_ETR 引脚配置
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    // 外部时钟配置
    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0f);

    // 时基单元配置
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 滤波器的分频系数
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数，1，2，3...
    TIM_TimeBaseStructure.TIM_Period = 10 - 1;                  // ARR寄存器的值，设定计数周期，到这个时间清零重新开始
    TIM_TimeBaseStructure.TIM_Prescaler = 1 - 1;                // PSC寄存器的值，分频的系数
    // 原频率 / [(ARR+1)*(PSC+1)] => +1：和数组下标一样，从0开始的

    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // 重复计数器，仅高级定时器用
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);

    // 使能TIM的更新中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 配置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 优先级分组
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // 响应优先级
    NVIC_Init(&NVIC_InitStructure);

    // 启动定时器
    TIM_Cmd(TIM2, ENABLE);
}

uint16_t Timer_GetCounter(void)
{

    return TIM_GetCounter(TIM2);
}
/*
void TIM2_IRQHandler(){
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
        number ++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
*/
