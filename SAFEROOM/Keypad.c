/*
* Keypad.c
*
* 
*  Author: rjfur
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "LCD.h"
#include "TWI.h"
#include "Keypad.h"
//#include "FSM.h"

//uint16_t
char keypad[4][4] = {	{'1', '2', '3','A'},
{'4', '5', '6','B'},
{'7', '8', '9','C'},
{'*', '0', '#', 'D'}};

void Keypad_Init()
{
	DDRC &= ~(1<<Keypad_pin); //pin PC0 input
	PORTC |= (1<<Keypad_pin); //enables pullup
	IOX_Write(0b00001111);
}

uint8_t IOX_Read(uint8_t ADDR)
{
	uint8_t S_Val = 0,DATA = 0;
	S_Val = TWI_START();
	//if(S_Val == TWI_START_VAL)
	S_Val = TWI_Transmit((PCF_ADDR | TWI_READ));
	//if(S_Val == TWI_WRITE_ACK)
	S_Val = TWI_Receive(TWI_ACK,&DATA);
	//if(S_Val == TWI_READ_ACK)
	TWI_STOP();
	//	DATA &= (0b1111);
	S_Val &= (0b1111);
	return S_Val;
}

void IOX_Write(uint8_t DATA)
{
	uint8_t S_Val = 0;
	S_Val = TWI_START();
	if(S_Val == TWI_SSTART)
	S_Val = TWI_Transmit((PCF_ADDR | TWI_WRITE));
	if(S_Val == TWI_WACK)
	TWI_Transmit(DATA);
	if(S_Val == TWI_WDACK)
	TWI_STOP();
}

void Keypad_Read(void)
{
	IOX_Write(MASK & P4);
	Key_Val = IOX_Read(Key_Val);
	if(Key_Val != 0x0F)
	{
		if(!(Key_Val & (1<<3)))
		Press |= keypad[0][0];
		if(!(Key_Val & (1<<2)))
		Press |= keypad[0][1];
		if(!(Key_Val & (1<<1)))
		Press |= keypad[0][2];
		if(!(Key_Val & (1<<0)))
		Press |= keypad[0][3];
		
	}
	
	IOX_Write(MASK & P5);
	Key_Val= IOX_Read(Key_Val);
	if(Key_Val != 0x0F)
	{
		if(!(Key_Val & (1<<3)))
		Press |= keypad[1][0];
		if(!(Key_Val & (1<<2)))
		Press |= keypad[1][1];
		if(!(Key_Val & (1<<1)))
		Press |= keypad[1][2];
		if(!(Key_Val & (1<<0)))
		Press |= keypad[1][3];
	}
	
	IOX_Write(MASK & P6);
	Key_Val = IOX_Read(Key_Val);
	if(Key_Val != 0x0F)
	{
		if(!(Key_Val & (1<<3)))
		Press |= keypad[2][0];
		if(!(Key_Val & (1<<2)))
		Press |= keypad[2][1];
		if(!(Key_Val & (1<<1)))
		Press |= keypad[2][2];
		if(!(Key_Val & (1<<0)))
		Press |= keypad[2][3];
	}
	
	IOX_Write(MASK & P7);
	Key_Val = IOX_Read(Key_Val);
	if(Key_Val != 0x0F)
	{
		if(!(Key_Val & (1<<3)))
		Press |= keypad[3][0];
		if(!(Key_Val & (1<<2)))
		Press |= keypad[3][1];
		if(!(Key_Val & (1<<1)))
		Press |= keypad[3][2];
		if(!(Key_Val & (1<<0)))
		Press |= keypad[3][3];
	}
	

}

/*ISR(PCINT0_vect)
{

	if(KEY_LOW)
	{
		STATE_Transition(DOORLOCK);
	}
}*/