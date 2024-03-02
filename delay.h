#ifndef    	__DELAY_H
#define 		__DELAY_H
#include "stm32f10x.h"

#ifdef __cplusplus
 extern "C" {
#endif
//----------KHAI BAO CAC HAM
void TIM3Init(void);
void Delay_ms(uint32_t dem);
void Delay_us(uint32_t dem);
#ifdef __cplusplus
}
#endif

#endif



