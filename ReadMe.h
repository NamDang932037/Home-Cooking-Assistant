// He thong bao chay va ho tro nau an
//Made by: Ban Neo giau ten

//Chip use: STM32F103C8T6 (Blue Pill)
//PIN OUT

//PORT A																	PORT B
//PA0: L298N Enable												PB0: Button 
//PA1: L298N IN1 (PWM)										PB6: SCL I2C LCD
//PA2: Buzzer control											PB7: SDA I2C LCD
//PA3: L298N IN2 (PWM)										
//PA4: LM35 ADC input
//PA5: Gas sensor input
//PA6: Smoke sensor input
//PA7: Flame sensor input
//PA8: Flame led
//PA9: Gas led
//PA10: Smoke led

/*
14.5mA 4.93V MQ135
4.5mA  4.91V MQ2
2.4mA 4.92V Flame sensor
1.04V 6micro ampere x4 resistor
4.96V 19.6mA buzzer

*/