/*
* servo.c
*
* Created: 10/30/2018 3:34:40 PM
*  Author: rjfur
*/
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "servo.h"

void T1pwm_Init(void)
{

	DDRB |= (1<<Servo_Pin);//set pin b1 as output my PWM pin

	//Set port B as output/configure as 8 channels of outputs
	// PB1 is now an output - corresponds to OCR1A

	TCCR1A |= (1<<COM1A1) | (0<<COM1A0);
	// set non-inverting mode

	TCCR1A |= (1<<WGM11) | (0<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS11);
	// set fast PWM Mode 14

	ICR1 = 39999; // For 20ms period


	//TCCR0B |= (1<<CS11);
	// set prescaler to 8 and starts PWM
	//return 0
}

void Servo_Open()
{
OCR1A = 1199; //-90?
}

void Servo_Close()
{
OCR1A = 4799; //90
}


/*	while(1)
{
OCR1A = 1119; //+ offset; //2000 for 1ms pulse width
// gives servo motor position
_delay_ms(3000);
OCR1A = 4899; //- offset;
_delay_ms(3000);
}*/

