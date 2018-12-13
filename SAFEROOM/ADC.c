/*
* ADC.c
*
* Created: 11/26/2018 6:25:03 PM
*  Author: rjfur
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "ADC.h"

void ADC_Init(uint8_t chan)
{
	//Control status reg A
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | ( 1<<ADPS2) | (1<<ADATE) | (1<<ADIE) | (1<<ADSC);
	// adc en | start conv | int en | set pre 128 | auto trig en

	// ADC MUX
	ADMUX |= (1<<REFS0);//set ref to AVCC
	//ADMUX |= ((chan & 0x0F)<<MUX0); //select ADC channel
	ADMUX |= (ADMUX & 0xF0) | (chan & 0x0F);
	//ADMUX |=  (0<<MUX3) | (0<<MUX2) | (1<<MUX1) | (1<<MUX0);// input select read ADC0?
	//ADMUX |=  (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0);// input select read ADC0?
	
	//Control status reg B
}
//void ADC_singleR() //for pot
//{
//	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADPS0) | (1<<ADPS1) | ( 1<<ADPS2) | (1<<ADATE) //| (1<<ADIE);
	// adc en | start conv | int en(taken out) | set pre 128 | auto trig en

	// ADC MUX
//	ADMUX |= (1<<REFS0);//set ref to AVCC
//	ADMUX |= ((chan)<<MUX0); //select ADC channel
//}
void ADC_Stop(void)
{
	
	ADCSRA = 0; // stop ADC sampling
}
void ADC_SingleRead()
{
ADCSRA |= (1<<ADSC);
_delay_ms(10);
ADC_Stop();
}

void ADC_Read(uint8_t select)

{
	switch(select)
	{
		case 1:
		ADC_Init(3); //potentiometer ADC3-
		//settemp_val = ADC;
		break;
		case 2:
		ADC_Init(6); //IR sensor 1 AD6
		IRresult1= ADC;
		break;
		case 3:
		ADC_Init(7); //IR sensor 1 AD7
		IRresult2= ADC;
		//selector=1;
		break;
	}
}

		ISR(ADC_vect)
		{
			//if(STATE_Current == SETTEMP)
			//{
				//ADC_Read(1);
			//}
			settemp_val = ADC;
			//if(current_state == 
		}