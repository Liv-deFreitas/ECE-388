/*
 * LCD.c
 *
 * Created: 10/9/2018 8:33:18 PM
 *  Author: rjfur
 */ 
 #define F_CPU 16000000UL
 #include <util/delay.h>

 #include <avr/io.h>
 #include <stdio.h>
 #include "TWI.h"
 #include "LCD.h"

 void LCD_Init(void)
{
	 TWI_Init();
	 Trans(0x33,0);
	 _delay_us(5);
	 Trans(0x32,0);
	 _delay_us(5);
	 Trans(0x28,0);
	 _delay_us(5);
	 Trans(0x0e,0);
	 _delay_us(5);
	 Trans(0x01,0);
	 _delay_us(5);
	Trans(0x06,0);
	 _delay_us(5);
	 Trans(0x0C,0); 
 }

void LCD_Print( char * str)
{
	int i= 0;
	while (str[i] != 0)
	{
		
		Trans(str[i], 1);
		++i;
		_delay_us(10);
	}
	return;
}
void LCD_Posit(unsigned char x, unsigned char y)
{
	unsigned char firstaddress[] = {0x80, 0xC0, 0x94, 0xD4};
	
	Trans(firstaddress[y] + x, 0);
	_delay_us(10);
}

 void LCD_Send(unsigned char DATA)
 {
	 uint8_t STATUS = 0;
	 STATUS = TWI_START();
	 if(STATUS == TWI_SSTART)
	 STATUS = TWI_Transmit(LCD1_ADDR | TWI_WRITE);
	 if(STATUS == TWI_WACK)
	 STATUS = TWI_Transmit(DATA | BACKLIGHT); // keep back light on
	 if(STATUS == TWI_WDACK)
	 TWI_STOP();
	 
 }
 void LCD_Pulse(unsigned char data)
 {
	 LCD_Send(En | data);
	 _delay_us(1);
	 LCD_Send(data & ~En);
	 _delay_us(50);
 }
 void bitdata(unsigned char data)
 {
	 LCD_Send(data);
	 LCD_Pulse(data);
 }
 
 void Trans(unsigned char data, uint8_t rsmode) // writes to either data or command register
 {
	 uint8_t uppernibble= (data & 0xF0); // masks nibbles
	 uint8_t lowernibble = ((data<<4) & 0xF0);
	 if(rsmode==1)
	 {
		 
		 bitdata(Rs | uppernibble);
		 bitdata(Rs | lowernibble);
	 }
	 else
	 {
		 
		 bitdata(uppernibble & ~Rs);
		 bitdata(lowernibble & ~Rs);
	 }
 }
 void LCD_Clear(void)
 {
	 LCD_Posit(15,0);
	 LCD_Print(" ");
	 LCD_Posit(15,1);
	 LCD_Print(" ");
 }