/*
 * Buttons.h
 *
 * Created: 11/25/2018 11:10:00 PM
 *  Author: rjfur
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#define HC_Button_Pin PB0
#define DR_Button_Pin PD7 //door button

//Climate buttons
#define CButton_Pressed !(PINB & (1<<HC_Button_Pin))
#define CButton_NotPressed (PINB & (1<<HC_Button_Pin))

//PCINT23
//door buttons
#define DButton_Pressed !(PIND & (1<<DR_Button_Pin))
#define DButton_NotPressed (PIND & (1<<DR_Button_Pin))
//#define NUM_OF_CONSECUTIVE_PRESSES 145000
//#define NUM_OF_CONSECUTIVE_NON_PRESSES 100

uint8_t HCstate;
uint8_t DRstate;

//int intConsecutivePresses; //= 0;
//int intConsecutiveNonPresses;// = 0;

//functions
void Button_setup();

void HC_states();

void Door_States();

void HCbutton_debounce();

void Close_Door();

void Open_Door();

#endif /* BUTTONS_H_ */