
#include "main.h"	
#include "adc.h"

void ADC_Configuration()
{
		//GPIO Config
		GPIO_InitTypeDef GPIO_InitStructure;
		//Enable clock AFIO
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		// Initialization struct
	ADC_InitTypeDef ADC_InitStruct;	
//cap xung clk cho bo ADC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
// Chon Che Do Cho Bo ADC
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
//Enable - Disable che do Scan
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
//Enable - Disable che do lien tuc
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
//Dinh nghia  Trigger ben ngoai de bat dau 1 chuyen doi ADC kenh Regular
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
// Enable kich thich chuyen doi tu ben ngoai
	ADC_ExternalTrigConvCmd(ADC1, ENABLE);
//Chon Kieu Luu Tru Du Lieu 
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
//Chon so luong kenh regular ADC su dung; cho phep 1 den 16
	ADC_InitStruct.ADC_NbrOfChannel = 1;
// Cau hinh ADC
	ADC_Init(ADC1, &ADC_InitStruct);
//Kich Hoat ADC1
	ADC_Cmd(ADC1, ENABLE);
//Bat Dau hieu chuan ADC1
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
 }
/*******************************************************************************
Noi Dung      :   Chon và doc gia tri ADC
Tham Bien     :   Khong.
Tra Ve        :   Khong.
*******************************************************************************/
uint16_t ADC1_Read()
{
//chon kenh chuyen doi ADC và so luong kenh chuyen doi, chu ky chuyen doi
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_71Cycles5);
// Start ADC conversion
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
// Wait until ADC conversion finished
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
//tra ve gia tri ADC
	return (ADC_GetConversionValue(ADC1));
}

double TempRead(void) {
		uint8_t i;
		double temp_val=0,tam1 = 0,tam2 = 0;
		for(i = 0; i < 5;i++) {
				tam1 += ((double)ADC1_Read()*330/4095); 
				Delay_ms(1);
		}
		temp_val = tam1/5;
		return temp_val;
	
}
/********************************* END OF FILE ********************************/	


