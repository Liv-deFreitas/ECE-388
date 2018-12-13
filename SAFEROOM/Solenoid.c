/*
 * Solenoid.c
 *
 * 
 *  Author: rjfur
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "Solenoid.h"

void SOL_Setup()
{
	DDRC |= (1 << SOL_PIN); // Set Sol as output
}
void Sol_Lock(void) // close door
{
	
	PORTC &= ~(1<<SOL_PIN);
}

void SOL_Unlock(void) // open unlock
{
	PORTC |= (1<<SOL_PIN);
}