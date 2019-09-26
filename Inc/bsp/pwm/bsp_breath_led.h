#ifndef __BSP_BREATH_LED_H__
#define __BSP_BREATH_LED_H__


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim4;
 
extern uint8_t indexWave[];

#define GENERAL_TIMx                TIM4
#define GENERAL_TIM_CLK_ENABLE()    __HAL_RCC_TIM4_CLK_ENABLE()
#define GENERAL_TIM_CLK_DISABLE()    __HAL_RCC_TIM4_CLK_DISABLE()


#define GENERAL_TIM_CH3_PORT        GPIOB
#define GENERAL_TIM_CH3_PIN         GPIO_PIN_8

#define GENERAL_TIM_IRQn            TIM4_IRQn
#define GENERAL_TIM_IRQHANDLER      TIM4_IRQHandler

// ��ʱ��Ԥ��Ƶ��
#define GENERAL_TIM_PRESCALER       1999

// ��ʱ�����ڣ� ������ֵ�ﵽ��ֵʱ���¶�ʱ�������ɶ�Ӧ�¼����ж�(�Զ���װ��ֵ)
#define GENERAL_TIM_PERIOD          255


void HAL_TIM_General_MspInit(TIM_HandleTypeDef* htim_base);
void General_TIMx_Init(void);

#endif
