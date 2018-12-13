/*
* Keypad.c
*
* Created: 11/29/2018 12:29:29 PM
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

//#define COL1  3  // P3 of PCF8574
//#define COL2  2  // P2 of PCF8574
//#define COL3  1  // P1 of PCF8574
//#define COL4  0  // P0
//#define ROW1  7  // P7 of PCF8574
//#define ROW2  6  // P6 of PCF8574
//#define ROW3  5  // P5 of PCF8574
//#define ROW4  4  // P4 of PCF8574

//const char keymap[4][4] = {	{1,2,3,A},		//column & row to button value
//{4,5,6,B},
//{7,8,9,C},
//{*,0,#,D}};

//const char columnMask [4] = { 0x7F, 0xBF, 0xDF, 0xEF };	//column select values

#define P4 0b01111111 // 0x7F
#define P5 0b10111111 // 0xBF
#define P6 0b11011111 // 0xDF
#define P7 0b11101111 // 0xEF
#define MASK 0b11111111 // 0xFF



#define PCF_ADDR (0x020<<1)
//15		14	13	12	11	10	9		8		7		6		5		4		3		2		1			0
//emergency	fl5	fl4	fl3	fl2	fl1	fl5dwn	fl4dwn	fl3dwn	fl2dwn	fl4up	fl3up	fl2up	fl1up	door close	door open
//uint16_t
 char keypad[4][4] = {	{'1', '2', '3','A'},
							{'4', '5', '6','B'},
							{'7', '8', '9','C'},
							{'*', '0', '#', 'D'}};




uint8_t PCF8574_SINGLEREAD(uint8_t ADDR)
{
	uint8_t STATUS = 0,DATA = 0;
	STATUS = TWI_START();
	//if(STATUS == TWI_START_VAL)
	STATUS = TWI_Transmit((PCF_ADDR | TWI_READ));
	//if(STATUS == TWI_WRITE_ACK)
	STATUS = TWI_Receive(TWI_ACK,&DATA);
	//if(STATUS == TWI_READ_ACK)
	TWI_STOP();
	//	DATA &= (0b1111);
	STATUS &= (0b1111);
	return STATUS;
}

void PCF8574_SINGLEWRITE(uint8_t DATA)
{
	uint8_t STATUS = 0;
	STATUS = TWI_START();
	if(STATUS == TWI_SSTART)
	STATUS = TWI_Transmit((PCF_ADDR | TWI_WRITE));
	if(STATUS == TWI_WACK)
	TWI_Transmit(DATA);
	if(STATUS == TWI_WDACK)
	TWI_STOP();
}


void readButtons(void)
{

	
	PCF8574_SINGLEWRITE(MASK & P4);
	result = PCF8574_SINGLEREAD(result);
	if(result != 0x0F)
	{
		if(!(result & (1<<3)))
		Press |= keypad[0][0];
		if(!(result & (1<<2)))
		Press |= keypad[0][1];
		if(!(result & (1<<1)))
		Press |= keypad[0][2];
		if(!(result & (1<<0)))
		Press |= keypad[0][3];
		
	}
	
	PCF8574_SINGLEWRITE(MASK & P5);
	result= PCF8574_SINGLEREAD(result);
	if(result != 0x0F)
	{
		if(!(result & (1<<3)))
		Press |= keypad[1][0];
		if(!(result & (1<<2)))
		Press |= keypad[1][1];
		if(!(result & (1<<1)))
		Press |= keypad[1][2];
		if(!(result & (1<<0)))
		Press |= keypad[1][3];
	}
	
	PCF8574_SINGLEWRITE(MASK & P6);
	result = PCF8574_SINGLEREAD(result);
	if(result != 0x0F)
	{
		if(!(result & (1<<3)))
		Press |= keypad[2][0];
		if(!(result & (1<<2)))
		Press |= keypad[2][1];
		if(!(result & (1<<1)))
		Press |= keypad[2][2];
		if(!(result & (1<<0)))
		Press |= keypad[2][3];
	}
	
	PCF8574_SINGLEWRITE(MASK & P7);
	result = PCF8574_SINGLEREAD(result);
	if(result != 0x0F)
	{
		if(!(result & (1<<3)))
		Press |= keypad[3][0];
		if(!(result & (1<<2)))
		Press |= keypad[3][1];
		if(!(result & (1<<1)))
		Press |= keypad[3][2];
		if(!(result & (1<<0)))
		Press |= keypad[3][3];
	}
	
	//PCF8574_SINGLEWRITE(0x0F);
	//PCF8574_SINGLEREAD(result);
	//PCIFR |= (1<<PCIF0);
}

//ISR(PCINT0_vect)
//	{
//if((PINB & (1<<0)))
//return;
//	if(KEY_LOW)
//{
//readButtons();
//}

//}