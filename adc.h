#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
 extern "C" {
#endif
//----------KHAI BAO CAC HAM CHO ADC.C
#include "main.h"	
#include "stm32f10x.h"
void ADC_Configuration(void);
uint16_t ADC1_Read(void);
double TempRead(void);

#ifdef __cplusplus
}
#endif

#endif
