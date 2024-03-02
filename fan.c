#include "fan.h"

void PWM_PA1_Setup(void) {
		TIM_OCInitTypeDef pwmInit;
		pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
		pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
		pwmInit.TIM_Pulse = 0;
		pwmInit.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC2Init(TIM2, &pwmInit);
}

void PWM_PA3_Setup(void) {
		TIM_OCInitTypeDef pwmInit;
		pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
		pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
		pwmInit.TIM_Pulse = 0;
		pwmInit.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC4Init(TIM2, &pwmInit);
}


void TIM2_Setup(void) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		TIM_TimeBaseInitTypeDef timerInit;
		timerInit.TIM_CounterMode = TIM_CounterMode_Up;
		timerInit.TIM_Period = 1000;
		timerInit.TIM_Prescaler = 71;
		TIM_TimeBaseInit(TIM2, &timerInit);
		TIM_Cmd(TIM2, ENABLE);
}

void PWM_GPIO_Setup(void) {
		GPIO_InitTypeDef GPIO_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;      		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;			
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		
		GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void EN_Setup(void) {
		GPIO_InitTypeDef GPIO_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void FanConfig(void) {
		TIM2_Setup();
		PWM_GPIO_Setup();
		PWM_PA1_Setup();
		PWM_PA3_Setup();
		EN_Setup();
}