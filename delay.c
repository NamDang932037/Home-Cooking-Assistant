#include "delay.h"
#include "main.h"

void TIM3Init(void) 
{		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
	
		TIM_TimeBaseInitStruct.TIM_Prescaler = 71; //bo chia tan so 72Mhz -> 1Mhz; 1tick = 1us
	//Thiet lap gia tri cua chu ky
	TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF; //bo dem
	//Thiet lap gia tri RCR
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	//Thiet lap he so chia cho bo TIMER
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	// Thiet lap cho TIMER dem len
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	// Thiet lap che do TimeBase
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM3,ENABLE);
}

void Delay_ms(uint32_t dem) {
		while(dem) {
		TIM_SetCounter(TIM3,0);
				while(TIM_GetCounter(TIM3)<1000);
				dem--;
		}
}
void Delay_us(uint32_t dem) {
		
		TIM_SetCounter(TIM3,0);
		while(TIM_GetCounter(TIM3)<(dem-1));
}	