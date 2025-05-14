#include "main.h"

/*
   @brief   This is an example program to demonstrate the use of setup and loop functions
            The project provides a setup for Initializing PWM timer on Advanced Timer 1 Peripheral
            Upon success compilation the binary will be directed to STM32/build/smps-controller.bin
            Upload the binary on your STM32 device with STLink ar any debugging Tool

    @author Abdulrahman S Jafari 
*/

TIM_HandleTypeDef htim1 ={0};
__IO uint32_t p_width ={20};

void setup(){

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_TIM1_CLK_ENABLE();


    GPIO_InitTypeDef gpioa8, gpioc13;

    //gpioc13 setup
    gpioc13.Pin = GPIO_PIN_13;
    gpioc13.Mode = GPIO_MODE_OUTPUT_PP;
    gpioc13.Speed = GPIO_SPEED_FREQ_MEDIUM;
    gpioc13.Pull = GPIO_NOPULL;

    //initializing gpioc13..
    HAL_GPIO_Init(GPIOC, &gpioc13);

    //gpioa8 setup
    gpioa8.Pin = GPIO_PIN_8;
    gpioa8.Mode = GPIO_MODE_AF_PP;
    gpioa8.Speed = GPIO_SPEED_FREQ_MEDIUM;
    gpioa8.Pull = GPIO_NOPULL;
    gpioa8.Alternate = GPIO_AF1_TIM1;

    //initializing gpioa8
    HAL_GPIO_Init(GPIOA, &gpioa8);
    
    tim_pwm_init();

}

void loop(){
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    HAL_Delay(1000);
}

void tim_pwm_init(){

    TIM_ClockConfigTypeDef xClockSourceConfig = {0};
    TIM_OC_InitTypeDef xConfigOC = {0};

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 47;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 100;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        error_handler();
    }

    xClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim1, &xClockSourceConfig) != HAL_OK)
    {
        error_handler();
    }
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
    {
        error_handler();
    }

    xConfigOC.OCMode = TIM_OCMODE_PWM1;
    xConfigOC.Pulse = p_width;
    xConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    xConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
    xConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &xConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        error_handler();
    }
    
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  
}