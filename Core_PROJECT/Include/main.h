/*
    @author Abdulrahman S Jafari
*/


#ifndef __MAIN_H
#define __MAIN_H

//including hal library front-end
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim1;

void error_handler(void);
void system_clock_init(void);
void htim1_init(void);
void tim_pwm_init(void);

//exported files
void loop(void);
void setup(void);

#endif