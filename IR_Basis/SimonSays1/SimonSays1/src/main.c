/**
 * Simon Says ECE 388 Lab Practical
 *
 * Liv de Freitas
 *
 * Note: most of this code is "Frankensteined" and repurposed code from the references listed in my Simon Says Practical test plan document 
 */

#include <asf.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

void InitADC();
uint16_t ReadADC(uint16_t ADCchannel);

int main (void)
{
	board_init(); //initialize xplained mini
	DDRB |= (1<<DDB3);//makes pb3 an output
	DDRC &= (0<<DDC0);//makes pc0 an input
	//PORTB |= (1<<PORTB0)

	InitADC();//initialize the ADC
	while(1){//once everything is initialized, continuously check to see if anyone is in range
		if(ReadADC(ADC0D) >= 280){
			PORTB |= (1<<PORTB3);    //If ADC value is at or above 280 (IR analog output of ~0.9V, hand distance of 6in) turn fan on
		}
		else {
			PORTB &= ~(1<<PORTB3);    //otherwise turn fan off
		}
	}
}
void InitADC()//initialize ADC
{
	ADMUX = (0b00 << REFS0);// Select Vref=AREF
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);//set prescaler to 128 so we have a 125Khz clock source and enable ADC
}
uint16_t ReadADC(uint16_t ADCchannel)//Read ADC value
{
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);//select ADC channel with mask	
	ADCSRA |= (1<<ADSC);//enter conversion mode
	while( ADCSRA & (1<<ADSC) )	;// wait until ADC conversion is complete
	return ADC;//return ADC value
}
