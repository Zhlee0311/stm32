#include "stm32f10x.h" // Device header

void PWM_Init(void)
{
    // 外设时钟使能
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    /* 端口复用，用不到可以注释掉
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    */
    
    // 配置GPIO端口用于输出PWM
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 使用复用推挽输出，因为输出源来自TIM2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 内部时钟配置
    TIM_InternalClockConfig(TIM2);

    // 时基单元配置
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 滤波器的分频系数
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数，1，2，3...
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;                 // ARR寄存器的值，设定计数周期，到这个时间清零重新开始
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;              // PSC寄存器的值，分频的系数
    // 原频率 / [(ARR+1)*(PSC+1)] => +1：和数组下标一样，从0开始的
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // 重复计数器，仅高级定时器用
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 配置输出比较单元
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; // CCR（捕获比较寄存器的值）
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);

    // 启动定时器
    TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare2(uint16_t Compare)
{
    TIM_SetCompare2(TIM2, Compare);
}
