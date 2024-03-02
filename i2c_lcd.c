#include "i2c_lcd.h"
#include "main.h"


uint8_t I2C1_Receive_Byte(uint8_t address) {
		/* Send START condition */
		uint8_t I2C_DataReceive;
    I2C_GenerateSTART(I2C1, ENABLE);
		I2C_ClearFlag(I2C1,I2C_FLAG_BUSY);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send PCF8574 address for write */
    I2C_Send7bitAddress(I2C1, address, I2C_Direction_Receiver);
	/* Test on EV6 and clear it */
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
		I2C_Cmd(I2C1,ENABLE);
    /* Send the byte to be written */
    I2C_DataReceive = I2C_ReceiveData(I2C1);
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    /* Send STOP condition */
    I2C_GenerateSTOP(I2C1, ENABLE);	
		return  I2C_DataReceive;
}

void I2C_Receive_Multi(uint8_t address,uint8_t *buffer, uint8_t len) {
		
    I2C_GenerateSTART(I2C1, ENABLE);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send PCF8574 address for write */
    I2C_Send7bitAddress(I2C1, address, I2C_Direction_Receiver);
	/* Test on EV6 and clear it */
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
		I2C_Cmd(I2C1,ENABLE);
	
		while(len) {
				if(len==1) {
						I2C_AcknowledgeConfig(I2C1,DISABLE);
						I2C_GenerateSTOP(I2C1,ENABLE);
				}
		if((I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))) {
				*buffer = I2C_ReceiveData(I2C1);
				buffer++;
				len--;
		}
		
		}
   
    I2C_AcknowledgeConfig(I2C1,ENABLE);
}



void LCD_Write_byte(uint8_t data)
{		I2C_ClearFlag(I2C1,I2C_FLAG_BUSY);
		//while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

		I2C_GenerateSTART(I2C_Chanel, ENABLE);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(I2C_Chanel, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send PCF8574 address for write */
    I2C_Send7bitAddress(I2C_Chanel, PCF8574_Address, I2C_Direction_Transmitter);
	/* Test on EV6 and clear it */
    while (!I2C_CheckEvent(I2C_Chanel, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
		I2C_Cmd(I2C1,ENABLE); // co hoac khong cung duoc
    /* Send the byte to be written */
    I2C_SendData(I2C_Chanel, data);
    /* Test on EV8_2 and clear it */
    while (!I2C_CheckEvent(I2C_Chanel, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
    /* Send STOP condition */
    I2C_GenerateSTOP(I2C_Chanel, ENABLE);		
}

// i2c lcd testing function
void LCD_init (void)
{
		/* Set 4-bits interface */
		LCD_Control_Write(0x30);		 
		Delay_ms(10);
		LCD_Control_Write(0x30);		 
		Delay_ms(10);
		LCD_Control_Write(0x30);		 
		Delay_ms(10);
		LCD_Control_Write(0x33);		 
		Delay_ms(10);
		LCD_Control_Write(0x32);
		Delay_ms(50);
		/* Start to set LCD function */
		LCD_Control_Write(0x28);
			Delay_ms(50);	
		/* clear LCD */
		LCD_Control_Write(0x01);
			Delay_ms(60);
		/* wait 60ms */
		
		/* set entry mode */
		LCD_Control_Write(0x06);	Delay_ms(50);
		/* set display to on */	
		LCD_Control_Write(0x0C);	Delay_ms(50);
		/* move cursor to home and set data address to 0 */
		LCD_Control_Write(0x02);	Delay_ms(50);
}
void LCD_Data_Write(char data)
{
		char data_u, data_l;
		uint8_t data_t[4],i=0;
		data_u = data&0xf0;
		data_l = (data<<4)&0xf0;
		data_t[0] = data_u|0x0d;  //en=1, rs=0
		data_t[1] = data_u|0x09;  //en=0, rs=0
		data_t[2] = data_l|0x0d;  //en=1, rs=0
		data_t[3] = data_l|0x09;  //en=0, rs=0
		for(i = 0;i<4;i++)
		{
				 LCD_Write_byte(data_t[i]);
	  }

}
void LCD_Control_Write(char data)
{
    char data_u, data_l;
		uint8_t data_t[4],i=0;
		data_u = data&0xf0;
		data_l = (data<<4)&0xf0;
		data_t[0] = data_u|0x04;  //en=1, rs=0
		data_t[1] = data_u|0x08;  //en=0, rs=0
		data_t[2] = data_l|0x04;  //en=1, rs=0
		data_t[3] = data_l|0x08;  //en=0, rs=0
		for(i = 0;i<4;i++)
		{
				 LCD_Write_byte(data_t[i]);
		}

}
void LCD_Send_String (char *str)
{
		while (*str) LCD_Data_Write (*str++);
}
void Delete_LCD(void)
{
		LCD_Control_Write(0x01);
		Delay_ms(20);
}

void LCD_Gotoxy(uint8_t x, uint8_t y) {
		if(!y) {
		LCD_Control_Write(x+0x80);
		Delay_ms(5);
		} else {
		LCD_Control_Write(x+0xC0);	
		Delay_ms(5);
		}
}

void LCD_Number(uint8_t num, uint8_t leng) {
		uint8_t i,temp;
		char kitu[leng];
		for(i = 0; i <leng; i++) {
				temp = num%10;
				num = num/10;
				kitu[i] = temp;
		}
		for(i = 0; i< leng; i++) {
				LCD_Data_Write(kitu[leng-1-i]+48);
		}
	
}


void LCD_Create_Custom_Char(uint8_t location, uint8_t* data_bytes)
{
		uint8_t i;
		// We only have 8 locations 0-7 for custom chars
		location &= 0x07; 
		// Set CGRAM address
		LCD_Control_Write(SET_CGRAM_ADDRESS|(location << 3));
		
		// Write 8 bytes custom char pattern
		for (i = 0; i < 8; i++) 
		{
			LCD_Data_Write(data_bytes[i]);
		}
}



void LCD_Write_Custom_Char( uint8_t x, uint8_t y, uint8_t location)
{
	LCD_Gotoxy(x,y);
	LCD_Data_Write(location);
}

void LCD_Clear(void) {
	LCD_Control_Write(0x01);
	Delay_ms(20);
}

void I2C_LCD_Configuration(void)
{
    // cap clock cho ngoai vi va I2C
		GPIO_InitTypeDef 					GPIO_InitStructure;
		I2C_InitTypeDef						I2C_InitStructure; 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);							// su dung kenh I2C1 cua STM32
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
	// cau hinh chan SDA va SCL
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;						
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		I2C_DeInit(I2C1);
    // cau hinh I2C
		I2C_ClearFlag(I2C1,I2C_FLAG_BUSY);
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x01; //Dia chi cua Master
    I2C_InitStructure.I2C_Ack = I2C_Ack_Disable; //Disable Ack bit
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;      
    I2C_InitStructure.I2C_ClockSpeed = 100000;	//Toc do truyen									
    I2C_Init(I2C1, &I2C_InitStructure);
    // cho phep bo I2C hoat dong
		I2C_ClearFlag(I2C1,I2C_FLAG_BUSY);
    I2C_Cmd(I2C1, ENABLE);
	
	}	