/*
* main1.c
*
* Created: 10/30/2018 1:29:46 PM
*  Author: rjfur
*/
#define F_CPU 16000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include "IRsensor.h"
#include <stdio.h>
#include <util/delay.h>
#include "servo.h"

int main (void)
{
	ADC_Init();
	sei();
	T1pwm_Init();
	//int offset = 600;
	while(1)
	{
		if (Myresult <= 200)
		{
			OCR1A = 1199; //+ offset; // for 1ms pulse width //-90
			// gives servo motor position
			_delay_ms(100);
		}
		else if (Myresult >= 201)
		{
			OCR1A = 4799; //- offset; //+90
			_delay_ms(100);
		}

		//else if
		//OCR1A = 1999 - offset;
		//_delay_ms(3000);
	}
	return 0;
}