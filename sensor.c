#include "sensor.h"

void StartSensor(void) {
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;      		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			
		//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	//PA5: Gas  PA6: Smoke  PA7: Flame
		Delay_ms(1000); //Delay cabli
}

void Ledconfig(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		//PA8 -> Flame
		//PA9 -> Gas
		//PA10 -> Smoke
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;	      		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
		// Buzzer output
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;      		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

