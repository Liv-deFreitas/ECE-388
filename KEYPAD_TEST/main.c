/*
 * KeypadTest.c
 *
 * Created: 11/30/2018 11:31:27 PM
 * Author : rjfur
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LCD.h"
#include "Keypad.h"
#include "TWI.h"

#define Password_Length 5

int main(void)
{

char pass_set[Password_Length] = "1234";
char pass_data[Password_Length];
uint8_t data_count = 0;
char customkey;
 LCD_Init();
 LCD_Clear();
 Keypad_Init();
 //setup my interrupt
	sei();
 //char KEYDATA[100] ; //print buffer
    while (1) 
    {
	LCD_Posit(0,0);
	LCD_Print("Enter Password:");
	readButtons();
	customkey = Press;
	if(customkey)
	{
	pass_data[data_count] = customkey; //store char into data array
	LCD_Posit(data_count,1);
	LCD_Print(pass_data);
	data_count++;
	}
	if (data_count == Password_Length-1)
	{
	LCD_Clear();
	LCD_Posit(0,0);
	
	if(!strcmp(pass_data,pass_set))
	{
	LCD_Print("CORRECT CODE");
	}
	else
	{
	LCD_Print("INCORRECT CODE");
	}
	}
	
	//itoa(Press,pass_data,10); //convert int val to string
	
	//LCD_Posit(0,1);
	//LCD_Print("helo");

    }
}
