/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "pwm/bsp_breath_led.h"
#include "led/bsp_led.h"


/**
  * 函数功能: 系统时钟配置
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void SystemClock_Config(void)
{      
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE; // 外部晶振，8MHz
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;                   // 开启HSE
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;    // HSE 1分频
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;               // SYSCLK使用PLL时钟
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9; // PLL 9倍频
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // 系统时钟：72MHz
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;        // AHB时钟：72MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;         // APB1时钟：36MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;         // APB2时钟：72MHz
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2); // FLASH延时2个CPU周期

    __HAL_RCC_AFIO_CLK_ENABLE();

    // HAL_RCC_GetHCLKFreq()/1000    1ms中断一次
    // HAL_RCC_GetHCLKFreq()/100000	 10us中断一次
    // HAL_RCC_GetHCLKFreq()/1000000 1us中断一次
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000000); // SysTick定时器时钟源选择HCLK, 定时周期1us 直接调用HAL_Delay()即可

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* 系统滴答定时器中断优先级配置 */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

int main(void)
{

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    
    /* Configure the system clock */
    SystemClock_Config();

    LED_GPIO_Init();

    General_TIMx_Init();
    // 启动通道PWM输出
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);

    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
}

/* 定时器溢出中断回调函数 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint8_t pwm_index = 1;   // PWM查表
    static uint8_t period_cnt = 0;  // 用于计算周期表
    // 输出的周期数大于10，输出下一种脉冲宽的PWM波
	// 一个呼吸灯的周期 = 0.0071 * 10 * 40 = 2.844s
    period_cnt++;
    if(period_cnt >= 10)
    {
        // 修改比较寄存器的值
        htim4.Instance->CCR3 = indexWave[pwm_index];
    
        pwm_index++;
        // 一个PWM脉冲表有40个元素
        if(pwm_index >= 40)
            pwm_index = 0;

         period_cnt = 0;   
    }

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
