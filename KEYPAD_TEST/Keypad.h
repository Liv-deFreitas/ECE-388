/*
 * Keypad.h
 *
 * Created: 11/29/2018 12:29:44 PM
 *  Author: rjfur
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
char Press;
	uint8_t result;
#define Keypad_pin PB1

#define KEY_LOW !(PINB & (1<<Keypad_pin))

uint8_t PCF8574_SINGLEREAD(uint8_t ADDR);

void PCF8574_SINGLEWRITE(uint8_t DATA); // write to LCD

void readButtons(void);

#endif /* KEYPAD_H_ */