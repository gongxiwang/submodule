#ifndef __BSP_LED_H__
#define __BSP_LED_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* 类型定义 ------------------------------------------------------------------*/
typedef enum
{
  LED_OFF = 0,
  LED_ON  = 1,
  LED_TOGGLE = 2,
}LEDState_TypeDef;
#define IS_LED_STATE(STATE)           (((STATE) == LED_OFF) || ((STATE) == LED_ON) || ((STATE) == LED_TOGGLE))

/* 宏定义 --------------------------------------------------------------------*/
#define LED1                          (uint8_t)0x01
#define LED2                          (uint8_t)0x02
#define LED3                          (uint8_t)0x04
#define IS_LED_TYPEDEF(LED)           (((LED) == LED1) || ((LED) == LED2) || ((LED) == LED3))


#define LED1_RCC_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED1_GPIO_PIN                 GPIO_PIN_8
#define LED1_GPIO                     GPIOB


#define LED2_RCC_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED2_GPIO_PIN                 GPIO_PIN_9
#define LED2_GPIO                     GPIOB


#define LED1_ON                       HAL_GPIO_WritePin(LED1_GPIO,LED1_GPIO_PIN,GPIO_PIN_RESET)    // 输出高电平
#define LED1_OFF                      HAL_GPIO_WritePin(LED1_GPIO,LED1_GPIO_PIN,GPIO_PIN_SET)  // 输出低电平
#define LED1_TOGGLE                   HAL_GPIO_TogglePin(LED1_GPIO,LED1_GPIO_PIN)                // 输出反转

#define LED2_ON                       HAL_GPIO_WritePin(LED2_GPIO,LED2_GPIO_PIN,GPIO_PIN_RESET)    // 输出高电平
#define LED2_OFF                      HAL_GPIO_WritePin(LED2_GPIO,LED2_GPIO_PIN,GPIO_PIN_SET)  // 输出低电平
#define LED2_TOGGLE                   HAL_GPIO_TogglePin(LED2_GPIO,LED2_GPIO_PIN)                // 输出反转




/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
void LED_GPIO_Init(void);
void LEDx_StateSet(uint8_t LEDx,LEDState_TypeDef state);

#endif  // __BSP_LED_H__

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
