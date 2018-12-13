/*
* PIR.c
*
* Created: 12/7/2018 5:21:53 PM
*  Author: rjfur
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "PIR.h"
#include "LEDs.h"

void PIR_Setup()
{
	DDRD &= ~(1<<PIR_PIN);//set PIR pin as input
}
void Room_Light()
{
	if(PIND&(1<<PIR_PIN)) //if PIR reads motion
	{
		Light_ON();
	}
	else
	{
		Light_OFF();
	}
}