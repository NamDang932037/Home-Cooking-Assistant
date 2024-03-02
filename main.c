#include "main.h"
double temp = 0; //Bien gia tri nhiet do
uint16_t tam = 0; //Bien tam
volatile uint8_t mode = 0;  //mode = 0: auto  mode = 1: CA
uint8_t flame,gas,smoke; //Cac bien trang thai cam bien
volatile uint8_t display = 1; //Bien hien thi LCD S
volatile uint8_t wait = 0; //Bien delay doc nhiet do
int main() {
		
		//Start product
		TIM3Init();
		I2C_LCD_Configuration();
		LCD_init();
		LCD_Clear();
		ADC_Configuration();
		StartSensor();
		Ledconfig();
		FanConfig();
		ButtonConfig();
		//Calibration time delay
		LCD_Gotoxy(0,0);
		LCD_Send_String("Smart Fire Alarm");
		LCD_Gotoxy(1,1);
		LCD_Send_String("Calibrating...");
		Delay_ms(1500);
	
		
		while(1) {
							
				while(mode == 0) {
							if(display == 1){
							LCD_Clear();
							LCD_Gotoxy(4,0);
							LCD_Send_String("HFP mode");
							display = 0;
							GPIO_ResetBits(GPIOA,GPIO_Pin_0);
							}
							
							//Read sensors
							gas = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5); //gas
							smoke = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6); //smoke
							flame = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7); //flame
							
							
							if(!wait) {
							temp = TempRead();
							wait = 10;
							LCD_Gotoxy(2,1);
							LCD_Send_String("TEMP: ");
							LCD_Gotoxy(7,1);
							LCD_Number((uint16_t)temp,2);
							LCD_Gotoxy(9,1);
							LCD_Send_String(".");
							LCD_Gotoxy(10,1);
							temp *=10;
							temp=(uint16_t)temp%10;
							LCD_Number(temp,1);
							LCD_Gotoxy(11,1);
							LCD_Data_Write(0xDF);
							LCD_Gotoxy(12,1);
							LCD_Send_String("C");
							}
							else wait--;
			
							
							while(gas == 0) { 
									//buzzer on, blue led on
									GPIO_SetBits(GPIOA,GPIO_Pin_9); //blue led
									LCD_Gotoxy(2,1);
									LCD_Send_String("GAS DETECTED");
									GPIO_SetBits(GPIOA,GPIO_Pin_2); //buzzer
									gas = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5); //gas
									if(gas == 1) {
											GPIO_ResetBits(GPIOA,GPIO_Pin_9);
											GPIO_ResetBits(GPIOA,GPIO_Pin_2);
											LCD_Gotoxy(0,1);
											LCD_Send_String("              ");
									}
							}
							
							while(smoke == 0) {
									//fan out, buzzer on, yellow led
									GPIO_SetBits(GPIOA,GPIO_Pin_10); //yellow led
									LCD_Gotoxy(0,1);
									LCD_Send_String("SMOKE DETECTED");
									GPIO_SetBits(GPIOA,GPIO_Pin_2); //buzzer
									//fan out on
									TIM_Cmd(TIM2,ENABLE);
									GPIO_SetBits(GPIOA,GPIO_Pin_0); //Set bit EN
									TIM_SetCompare2(TIM2,990);
									TIM_SetCompare4(TIM2,0);
									
									smoke = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6); //smoke
									if(smoke == 1) {
											GPIO_ResetBits(GPIOA,GPIO_Pin_10);
											Delay_ms(20);
											GPIO_ResetBits(GPIOA,GPIO_Pin_2);
											Delay_ms(20);
											LCD_Gotoxy(0,1);
											LCD_Send_String("               ");
											Delay_ms(20);
											//fan out off
											TIM_SetCompare2(TIM2,0);
											TIM_Cmd(TIM2,DISABLE);
											GPIO_ResetBits(GPIOA,GPIO_Pin_0);
									}
							}
							
							while(flame == 0) {
									//led red, buzzer on
									GPIO_SetBits(GPIOA,GPIO_Pin_8); //red led
									Delay_ms(20);
									GPIO_SetBits(GPIOA,GPIO_Pin_2); //buzzer
									Delay_ms(20);
									LCD_Gotoxy(0,1);
									LCD_Send_String("FLAME DETECTED");
									flame = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7); //flame
									if(flame == 1) {
											GPIO_ResetBits(GPIOA,GPIO_Pin_8);
											Delay_ms(20);
											GPIO_ResetBits(GPIOA,GPIO_Pin_2);
											Delay_ms(20);
											LCD_Gotoxy(0,1);
											LCD_Send_String("              ");
									}
							}
				Delay_ms(500);
						
				}
			
				while(mode == 1){
				
							if(display == 1){
							LCD_Clear();
							LCD_Gotoxy(4,0);
							LCD_Send_String("CA mode");
							display--;
							GPIO_ResetBits(GPIOA,GPIO_Pin_0);
							}
	
							//Read sensors
							gas = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5); //gas
							smoke = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6); //smoke
							flame = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7); //flame
							if(!wait) {
							//tam = TempRead();
							temp = TempRead();
							wait = 10;
							LCD_Gotoxy(0,1);
							LCD_Send_String("                ");
							LCD_Gotoxy(2,1);
							LCD_Send_String("TEMP: ");
							LCD_Gotoxy(7,1);
							LCD_Number((uint16_t)temp,2);
							LCD_Gotoxy(9,1);
							LCD_Send_String(".");
							LCD_Gotoxy(10,1);
							tam = temp*10;
							tam=(uint16_t)tam%10;
							LCD_Number(tam,1);
							LCD_Gotoxy(11,1);
							LCD_Data_Write(0xDF);
							LCD_Gotoxy(12,1);
							LCD_Send_String("C");
							}
							else wait--;
							
							
							if(((temp<32)&smoke&gas) == 1) {
									//Normal
									//Led off
									GPIO_ResetBits(GPIOA,GPIO_Pin_8);
									GPIO_ResetBits(GPIOA,GPIO_Pin_9);
									GPIO_ResetBits(GPIOA,GPIO_Pin_10);
									//Buzzer off
									Delay_ms(20);
									GPIO_ResetBits(GPIOA,GPIO_Pin_2);
								
									//fan off
									TIM_Cmd(TIM2,DISABLE);
									GPIO_ResetBits(GPIOA,GPIO_Pin_0);
									TIM_SetCompare2(TIM2,0);
									TIM_SetCompare4(TIM2,0);
							}
							else if(((temp>32)&(smoke)&(gas)) == 1) {
							//fan in temp >32 everything normal
									//Led off
									GPIO_ResetBits(GPIOA,GPIO_Pin_8);
									Delay_ms(20);
									GPIO_ResetBits(GPIOA,GPIO_Pin_9);
									Delay_ms(20);
									GPIO_ResetBits(GPIOA,GPIO_Pin_10);
									Delay_ms(20);
									
									//Buzzer off
									GPIO_ResetBits(GPIOA,GPIO_Pin_2);
									//Fan in 
									TIM_Cmd(TIM2,ENABLE);
									Delay_ms(20);
									GPIO_SetBits(GPIOA,GPIO_Pin_0);
									Delay_ms(20);
									TIM_SetCompare2(TIM2,0);
									Delay_ms(20);
									TIM_SetCompare4(TIM2,990);
							}
							else if((smoke==0)&&(gas==0)){
						//both smoke and gas detected
									//Led on
									GPIO_SetBits(GPIOA,GPIO_Pin_9);
									Delay_ms(20);
									GPIO_SetBits(GPIOA,GPIO_Pin_10);
									Delay_ms(20);
									//Buzzer on
									GPIO_SetBits(GPIOA,GPIO_Pin_2);
									Delay_ms(20);	
									//Fan off
									TIM_Cmd(TIM2,DISABLE);
									GPIO_ResetBits(GPIOA,GPIO_Pin_0);
									TIM_SetCompare2(TIM2,0);
									TIM_SetCompare4(TIM2,0);
								  //LCD Display
									LCD_Gotoxy(0,1);
									LCD_Send_String("                ");
									LCD_Gotoxy(0,1);
									LCD_Send_String("GAS&SMK DETECTED");
						}
							else if(((~(smoke))&gas) == 1) {
							//fan out	+ led smoke
									GPIO_SetBits(GPIOA,GPIO_Pin_10); //yellow led
									Delay_ms(20);
									GPIO_ResetBits(GPIOA,GPIO_Pin_2); //buzzer
									Delay_ms(20);
									//LCD Display
									LCD_Gotoxy(0,1);
									LCD_Send_String("                ");
									LCD_Gotoxy(1,1);
									LCD_Send_String("SMOKE DETECTED");
									
									//fan out on
									TIM_Cmd(TIM2,ENABLE);
									Delay_ms(20);
									GPIO_SetBits(GPIOA,GPIO_Pin_0);
									TIM_SetCompare2(TIM2,990);
									TIM_SetCompare4(TIM2,0);
							}
							
							else if(((smoke)&(~(gas))) == 1) {
							//gas detected -> led gas + buzzer
									//Led on
									GPIO_SetBits(GPIOA,GPIO_Pin_9);
									Delay_ms(20);
									//Buzzer on
									GPIO_SetBits(GPIOA,GPIO_Pin_2);
									Delay_ms(20);
									//fan off
									TIM_Cmd(TIM2,DISABLE);
									Delay_ms(20);
									GPIO_ResetBits(GPIOA,GPIO_Pin_0);
									TIM_SetCompare2(TIM2,0);
									TIM_SetCompare4(TIM2,0);
									//LCD Display
										LCD_Gotoxy(0,1);
									LCD_Send_String("                ");
									LCD_Gotoxy(2,1);
									LCD_Send_String("GAS DETECTED");
							}
						Delay_ms(500);	
						}
						
			}
	
}


void EXTI0_IRQHandler(void) {
		//chong rung
		
		Delay_ms(50);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)== 0) {
		display++;
				if(mode == 0) {
							mode = 1;
							wait = 0;
							Delay_ms(30);
							GPIO_ResetBits(GPIOA,GPIO_Pin_0);
							Delay_ms(30);
							TIM_Cmd(TIM2,DISABLE);
				}
				else {
							mode = 0;
							wait = 0;
							Delay_ms(30);
							GPIO_ResetBits(GPIOA,GPIO_Pin_0);
							Delay_ms(30);
							TIM_SetCompare4(TIM2,0);
							TIM_Cmd(TIM2,DISABLE);
				}
			}
		
		EXTI_ClearITPendingBit(EXTI_Line0);
		
}
