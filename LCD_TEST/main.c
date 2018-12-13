/*
 * LCDtesting.c
 *
 * Created: 11/17/2018 11:48:16 PM
 * Author : rjfur
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"

int main(void)
{
LCD_Init();
  
    while (1) 
    {
	LCD_Clear();
	LCD_Posit(0,0);
	LCD_Print("Hello");
	LCD_Posit(0,1);
	LCD_Print("Testing");
    }
return 0;
}

