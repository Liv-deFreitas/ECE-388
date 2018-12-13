/*
* buttons.c
*
* Created: 11/25/2018 11:09:26 PM
*  Author: rjfur
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "Buttons.h"
#include "LCD.h"
#include "LCD2.h"
#include "LEDs.h"
#include "Fans.h"
#include "Solenoid.h"
#include "servo.h"
#include "Keypad.h"
#include "FSM.h"

void Button_setup()
{
	
	DDRB &= ~(1<<HC_Button_Pin);//set PB0 as input
	DDRD &= ~(1<<DR_Button_Pin);//set PD7 as input
}


void HC_states()
{
	//int HCstate;
	switch (HCstate)
	{
		//1 HEAT mode
		case 1:
		Fan_State = 2; //Fans for Heat
		LCD_Posit(8,1);
		LCD_Print("HEAT");
		RED_on();
		BLU_off();
		break;
		
		//2 COOL mode
		case 2:
		Fan_State = 3; //Fans for cool
		LCD_Posit(8,1);
		LCD_Print("COOL");
		BLU_on();
		RED_off();
		break;
		//3 OFF
		case 3:
		Fan_State = 4; //Fans for off
		LCD_Posit(8,1);
		LCD_Print("OFF");
		LCD_Posit(14,1);
		LCD_Print("  ");
		
		RED_off();
		BLU_off();
		break;
		
		//default AUTO
		default:
		Fan_State = 1; //Fans for auto
		LCD_Posit(8,1);
		LCD_Print("AUTO");
		
	}
}	
void Door_States()
{
switch (DRstate)
{
	//1 Door Open
	case 1:
	//LCD_Clear();
	LCD2_Posit(2,0);
	LCD2_Print("DOOR OPENING");
//	SOL_Unlock();
	//_delay_ms(800);
	//Servo_Open();
	//_delay_ms(500);
	break;
	
	//2 Door Close
	case 2:
	//LCD_Clear();
	LCD2_Posit(2,0);
	LCD2_Print("DOOR CLOSING");
	//Servo_Close();
	//_delay_ms(10000);
	//Sol_Lock();
	//_delay_ms()
	break;

	default:
	LCD2_Posit(4,0);
	LCD2_Print("SAFEROOM");

}
}
void Close_Door()
{
//LCD_Clear();
//LCD_Posit(2,0);
//LCD_Print("DOOR CLOSING");
Servo_Close();
_delay_ms(800);
Sol_Lock();
_delay_ms(500);
}

void Open_Door()
{
SOL_Unlock();
_delay_ms(800);
Servo_Open();
_delay_ms(500);
}


ISR(PCINT2_vect)
{
if(DButton_Pressed)
{
	_delay_ms(24);
}

if(DButton_Pressed)
{
if (STATE_Current == DORMANT)
{
	STATE_Transition(DOORLOCK);
}
	if (DRstate <= 2)
	{
		DRstate++;
	}
	else {
	LCD2_Clear();
		DRstate = 1;
	}
}
else
{
	DRstate = DRstate;

}
}

ISR(PCINT0_vect)
{ //if(KEY_LOW)
	//{
	//	_delay_ms(15);
//	}
	//if(KEY_LOW)
	//{
		//DRstate = 1;
	//	STATE_Transition(DOORLOCK);
	//}
	
if(CButton_Pressed)
{
	_delay_ms(24);
}
if(CButton_Pressed)
{
LCD_Posit(8,1);
//LCD_Clear();
LCD_Print("    ");
if (HCstate <= 3)
{
HCstate++;
}
else {
HCstate = 1;
}
}
else
{
HCstate = HCstate;

}
}


/*
void HCbutton_debounce()
{
	if(Button_Pressed) {										// if button is pressed (logic low)
		intConsecutivePresses++;											// increment counter for number of presses
		if(intConsecutivePresses >= NUM_OF_CONSECUTIVE_PRESSES) {			// if enough presses to constitute a press
			LCD_Posit(8,1);
			LCD_Print("    ");
			if (HCstate <= 3)
			{
				HCstate++;
			}
			else {
				HCstate = 1;
			}
			intConsecutivePresses = 0;										// and reset press counts
			intConsecutiveNonPresses = 0;
		}
		} else if(Button_NotPressed) {						// else if button is not pressed (logic HIGH)
		intConsecutiveNonPresses++;											// increment counter for number of non-presses
		if(intConsecutiveNonPresses >= NUM_OF_CONSECUTIVE_NON_PRESSES) {	// if enough consecutive non-presses that we are convinced the switch is not being pressed
			intConsecutivePresses = 0;										// reset press counts
			intConsecutiveNonPresses = 0;
			HCstate = HCstate;
		}
		} else {
		// ideally should never get here, but may occasionally due to timing
	}
}
*/
