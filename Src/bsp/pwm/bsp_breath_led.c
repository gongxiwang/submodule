#include "pwm/bsp_breath_led.h"

TIM_HandleTypeDef htim4;

uint8_t indexWave[] = {1,1,2,2,3,4,6,8,10,14,19,25,33,44,59,80,107,143,191,255,
                        255,191,143,107,80,59,44,33,25,19,14,10,8,6,4,3,2,2,1,1};

static void Error_Handler(void);

/* 定时器硬件初始化, 实际上是对msp.c中HAL_TIM_Base_MspInit()的重写 */
void HAL_TIM_General_MspInit(TIM_HandleTypeDef* htim_base)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if(htim_base->Instance == GENERAL_TIMx)
    {
        // TIM4时钟使能
        GENERAL_TIM_CLK_ENABLE();
        // TIM4的通道3功能引脚IO口初始化
        GPIO_InitStruct.Pin = GENERAL_TIM_CH3_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        HAL_GPIO_Init(GENERAL_TIM_CH3_PORT, &GPIO_InitStruct);        
    }

}

/* TIM4初始化并配置为PWM输出功能 */
void General_TIMx_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;
    // TIM4向上计数模式配置
    // 频率 = 72MHz / ((1+1999)*(1+255)) = 140.625Hz = 0.0071s
    htim4.Instance = GENERAL_TIMx;
    htim4.Init.Prescaler = GENERAL_TIM_PRESCALER;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = GENERAL_TIM_PERIOD;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    if(HAL_TIM_Base_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }
    // 内部时钟源
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;  
    if(HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }

    if(HAL_TIM_PWM_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;                 // 触发输出复位
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;        // 不使能主从模式
    if(HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    // PWM输出模式配置
    // 占空比 = sConfigOC.Pulse / htim4.Init.Period
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse =  0;                          // 待装入捕获比较寄存器的值
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;     // 小于预装载值时为高电平
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if(HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler();
    }
    
    HAL_TIM_General_MspInit(&htim4);

}

static void Error_Handler(void)
{

    while (1)
    {
        /* code */
    }
    
}
