/*
* IRsensor.c
*
* Created: 10/29/2018 4:47:40 PM
* Author : rjfur
*/
//Clock going into ADC cannot exceed 200KHz(w/16MHZclk=16MHz/200KHz=80)
//Prescaler set to 128 = 125KHz

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "IRsensor.h"

void ADC_Init(void){
	//Control status reg A
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | ( 1<<ADPS2) | (1<<ADATE);
	// adc en | start conv | int en | set pre 128 | auto trig en

	// ADC MUX
	ADMUX |= (1<<REFS0); //set ref to AVCC
	ADMUX |=  (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0);// input select read ADC0?
	// Pin PC0
	//Control status reg B
}
/*
void T0_Init(void)
{
// Control reg B clk source slc ---/1024
TCCR0B |= (1<<CS02) | (0<<CS01) | (1<<CS00);
// Control reg A mode of op slc ----CTC(clearoncmpmatch)
TCCR0A |= (0<<WGM02) | (1<<WGM01) | (0<<WGM00);
// Output Compare reg
OCR0A = //when matches counter flag is set
//Timer counter reg
TCNT0 = 0; //counter clears to 0 when match//compareing to OCR
//Timer interrupt mask reg
TIMSK0 = (1<<OCIE0A);//En int compmatch
} */

void ADC_Stop(void)
{
	
	ADCSRA = 0; // stop ADC sampling
}

ISR(ADC_vect)
{

	Myresult=ADC; //ADC is my 10-bit output

}