
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
 extern "C" {
#endif
//-----------------------GOI CAC THU VIEN CHUAN---------------------------------//
#include  <stdarg.h>//xu ly so
#include  <string.h>//xu ly kieu chuoi ky tu
#include  <ctype.h>//bao gom cac hoam dung de phan lop cac ky tu boi cac kieu hay dung chuyen doi viet hoa va viet thuong
#include  <stdlib.h>//cac phep toan
#include  <stdio.h>//Cung cap cac dinh dang IN/OUT trong C
#include 	"math.h"
//------------------------GOI THU VIEN DUNG CHO PROJECT ----------------------//
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
//------------------------GOI THU VIEN HAM NGUOI DUNG VIET------------------------//
#include "delay.h"
#include "i2c_lcd.h"
#include "adc.h"
#include "sensor.h"
#include "fan.h"
#include "exti.h"
//------------------------KHAI BAO CAC HAM CHO HAM main.c-------------------------//

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/*****************************END OF FILE****************************************/
