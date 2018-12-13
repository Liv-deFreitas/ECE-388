/*
* Fans.h
*
*
*  Author: rjfur
*/


#ifndef FANS_H_
#define FANS_H_

//LED pins
#define TFan_PIN PB2 //should be PD0
#define HFan_PIN PD4
volatile uint8_t setv;
int LED_state;
int Fan_State;

//Functions
void TFan_on();

void TFan_off();

void HFan_on();

void HFan_off();

void Fan_Control();

#endif /* FANS_H_ */