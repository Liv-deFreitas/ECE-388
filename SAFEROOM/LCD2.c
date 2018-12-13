/*
 * LCD2.c
 *
 *
 *  Author: rjfur
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>

#include "TWI.h"
#include "LCD2.h"
#include "FSM.h"
#include "Buttons.h"

void LCD2_Init(void)
{
	TWI_Init();
	LCD2_DWrite(0x33,0);
	_delay_us(5);
	LCD2_DWrite(0x32,0);
	_delay_us(5);
	LCD2_DWrite(0x28,0);
	_delay_us(5);
	LCD2_DWrite(0x0e,0);
	_delay_us(5);
	LCD2_DWrite(0x01,0);
	_delay_us(5);
	LCD2_DWrite(0x06,0);
	_delay_us(5);
	LCD2_DWrite(0x0C,0);
}

void LCD2_Print( char * str)
{
	int i= 0;
	while (str[i] != 0)
	{
		
		LCD2_DWrite(str[i], 1);
		++i;
		_delay_us(10);
	}
	return;
}
void LCD2_Posit(unsigned char x, unsigned char y)
{
	unsigned char firstaddress[] = {0x80, 0xC0, 0x94, 0xD4};
	
	LCD2_DWrite(firstaddress[y] + x, 0);
	_delay_us(10);
}

void LCD2_Send(unsigned char DATA) //add selection input to send to other LCD just change address?
{
	uint8_t STATUS = 0;
	STATUS = TWI_START();
	if(STATUS == TWI_SSTART)
	STATUS = TWI_Transmit(LCD2_ADDR | TWI_WRITE);
	if(STATUS == TWI_WACK)
	{
	if (STATE_Current == DOORLOCK)
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

void LCD2_Pulse(unsigned char data)
{
	LCD2_Send(En | data);
	_delay_us(1);
	LCD2_Send(data & ~En);
	_delay_us(50);
}
void bitdata2(unsigned char data)
{
	LCD2_Send(data);
	LCD2_Pulse(data);
}

void LCD2_DWrite(unsigned char data, uint8_t rsmode) // writes to data or command
{
	uint8_t uppernibble= (data & 0xF0); // mask
	uint8_t lowernibble = ((data<<4) & 0xF0);
	if(rsmode==1)
	{
		
		bitdata2(Rs | uppernibble);
		bitdata2(Rs | lowernibble);
	}
	else
	{
		
		bitdata2(uppernibble & ~Rs);
		bitdata2(lowernibble & ~Rs);
	}
}

void LCD2_Clear(void)
{
	LCD2_DWrite(0x01,0); // clear the LCD go to first line first position
	LCD2_DWrite(LineOne,0);
}