/*
 * DHT_TEST.c
 *
 * Created: 11/21/2018 10:37:55 AM
 * Author : rjfur
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "LCD.h"
#include "DHT11.h"

int main(void)
{
int8_t temp = 0;
int8_t humid = 0;
	LCD_Init();
	char DHTDATA[100] ; //print buffer
	while (1)
	{
		
	if (DHT_GetTH(&temp, &humid) != -1)
	{
			LCD_Clear();
			LCD_Posit(0,0);
			itoa(temp,DHTDATA,10);
			LCD_Print(DHTDATA);
			}
		
		else {

			//hello test
			LCD_Clear();
			LCD_Posit(0,0);
			LCD_Print("ERROR");
			}
		//Retrieve DATA from DHT11
		_delay_ms(1000);
	}
	return 0;
}