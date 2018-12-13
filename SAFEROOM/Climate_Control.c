/*
* Climate_Control.c
*
* 
*  Author: rjfur
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "Climate_Control.h"
#include "LCD.h"
//#include "FSM.h"

void Potentio_setup()
{
	DDRC &= ~(1<<Pot_PIN);//set PC3 as input
}
void POT_Divider()
{
	settemp_val = settemp_val / 10.33; //divide analog value for 0-99
}

void POT_Read()
{
ADC_Read(1);
}

void POT_Disp()
{
	POT_Divider();
	char POTdata[100];
	//settemp_val / 10;
	itoa(settemp_val,POTdata,10);
	LCD_Posit(14,1);
	LCD_Print(POTdata);
}

void GetSet_Disp()
{
	char Tsetbuff[100]; //buffer
	maxval = 80.0;
	minval = 65.0;

	// Get current value
	POT_Divider();
	setvalue = settemp_val;
	
	if (setvalue > maxval)
	{
		LCD_Posit(12,0);
		LCD_Print("S:80");
		itoa(setvalue,Tsetbuff,10);
		LCD_Print(Tsetbuff);
	}
	else if (setvalue < minval)
	{
		LCD_Posit(12,0);
		LCD_Print("S:65");
		itoa(setvalue,Tsetbuff,10);
		LCD_Print(Tsetbuff);
	}
	else
	{
		LCD_Posit(12,0);
		LCD_Print("S:");
		itoa(setvalue,Tsetbuff,10);
		LCD_Print(Tsetbuff);
	}
}
void Temp_AUTO()
{
LCD_Posit(12,0);
LCD_Print("S:75");
}

void POT_CLEAR()
{
LCD_Posit(14,1);
LCD_Print("  ");
}

/*ISR(PCINT1_vect)
{
//LCD_Clear();
//LCD_Posit(7,0);
//LCD_Print("SET TEMP");
POT_Disp();
//_delay_ms(2000);
//LCD_Clear();
}*/