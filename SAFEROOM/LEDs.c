/*
 * LEDs.c
 *
 * Created: 11/22/2018 3:15:24 PM
 *  Author: rjfur
 */ 
 
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <stdio.h>

 #include "LEDs.h"

 void RED_on()
{
DDRD |= (1 << RED_PIN); // Set RLED as output
PORTD |= (1 << RED_PIN); //Turn on RLED
}

void RED_toggle()
{
DDRD |= (1 << RED_PIN); // Set RLED as output
PORTD ^=(1 << RED_PIN); //toggle RLED
} 

void RED_off()
{
PORTD &= ~(1 << RED_PIN); //Turn off RLED
}

void BLU_on()
{
DDRD |= (1 << BLUE_PIN); // Set BLED as output
PORTD |= (1 << BLUE_PIN); //Turn on BLED
}

void BLU_off()
{
PORTD &= ~(1 << BLUE_PIN); //Turn off BLED
}

void Light_ON()
{
	DDRD |= (1 << LIGHT_PIN); // Set Light as output
	PORTD |= (1 << LIGHT_PIN); //Turn on Light
}

void Light_OFF()
{
	PORTD &= ~(1 << LIGHT_PIN); //Turn off Light
}