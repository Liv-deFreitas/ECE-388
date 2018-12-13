/*
* LCD.c
*
* Created: 10/9/2018 8:33:18 PM
*  Author: rjfur
*/

#define F_CPU 16000000UL
#include <util/delay.h>

#include "TWI.h"
#include "LCD.h"
#include "FSM.h"
#include "Buttons.h"

void LCD_Init(void)
{
	TWI_Init();
	LCD_DWrite(0x33,0);
	_delay_us(5);
	LCD_DWrite(0x32,0);
	_delay_us(5);
	LCD_DWrite(0x28,0);
	_delay_us(5);
	LCD_DWrite(0x0e,0);
	_delay_us(5);
	LCD_DWrite(0x01,0);
	_delay_us(5);
	LCD_DWrite(0x06,0);
	_delay_us(5);
	LCD_DWrite(0x0C,0);
}

void LCD_Print( char * str)
{
	int i= 0;
	while (str[i] != 0)
	{
		
		LCD_DWrite(str[i], 1);
		++i;
		_delay_us(10);
	}
	return;
}
void LCD_Posit(unsigned char x, unsigned char y)
{
	unsigned char firstaddress[] = {0x80, 0xC0, 0x94, 0xD4};
	
	LCD_DWrite(firstaddress[y] + x, 0);
	_delay_us(10);
}

void LCD_Send(unsigned char DATA) //add selection input to send to other LCD just change address?
{
	uint8_t STATUS = 0;
	STATUS = TWI_START();
	if(STATUS == TWI_SSTART)
	STATUS = TWI_Transmit(LCD1_ADDR | TWI_WRITE);
	if(STATUS == TWI_WACK)
	{
		if (STATE_Current == CLIMATECONTROL)
		{
			STATUS = TWI_Transmit(DATA | BACKLIGHT);
		}
		else
		{
			STATUS = TWI_Transmit(DATA);
		}
	}
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

void LCD_DWrite(unsigned char data, uint8_t rsmode) // writes to either data or command register
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

void LCD_DISPOFF()
{
	LCD_DWrite(LCD_DisplayOff,0);
	_delay_ms(80);

}

void LCD_Clear(void)
{
	LCD_DWrite(0x01,0); // clear the LCD go to first line first position
	LCD_DWrite(LineOne,0);
}