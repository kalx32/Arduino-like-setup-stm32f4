
/*
    @author:  Abdulrahman S Jafari
*/

#include "main.h"


int main(int argc, char** argv){
    HAL_Init(); //low level initialization...
    system_clock_init();
    setup();

    while(1){
        loop();
    }

    return 0;
}

void error_handler(){
    __disable_irq();
    while(1); //will wait indefinetly untill IWDG trigger reset
}

void HAL_MspInit(){
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
}

//low level clock setup
void system_clock_init() {

    RCC_OscInitTypeDef rcc_osc ={0};
    RCC_ClkInitTypeDef rcc_clk ={0};

    rcc_osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    rcc_osc.HSEState = RCC_HSE_ON;
    rcc_osc.PLL.PLLSource =RCC_PLLSOURCE_HSE;
    rcc_osc.PLL.PLLState =RCC_PLL_ON;
    rcc_osc.PLL.PLLM = 25;
    rcc_osc.PLL.PLLN = 192;
    rcc_osc.PLL.PLLP = RCC_PLLP_DIV4;
    rcc_osc.PLL.PLLQ = 4;

    //configure oscillator
    if(HAL_RCC_OscConfig(&rcc_osc) != HAL_OK){
        error_handler();
    }

    rcc_clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_SYSCLK;
    rcc_clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    rcc_clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    rcc_clk.APB1CLKDivider = RCC_HCLK_DIV2;
    rcc_clk.APB2CLKDivider = RCC_HCLK_DIV1;

    //configuring system clock
    if(HAL_RCC_ClockConfig(&rcc_clk, FLASH_LATENCY_1) != HAL_OK){
        error_handler();
    }
}


__attribute__((weak)) void setup(){

}

__attribute__((weak)) void loop(){
    
}