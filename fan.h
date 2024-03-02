#ifndef __FAN_H
#define __FAN_H

#ifdef __cplusplus
 extern "C" {
#endif
//----------KHAI BAO CAC HAM CHO ADC.C
#include "main.h"	
#include "stm32f10x.h"

void PWM_PA1_Setup();
void PWM_PA3_Setup();
void TIM2_Setup();
void PWM_GPIO_Setup();
void EN_Setup();
void FanConfig();
#ifdef __cplusplus
}
#endif

#endif