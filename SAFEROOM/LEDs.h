/*
 * LEDs.h
 *
 * Created: 11/22/2018 3:15:51 PM
 *  Author: rjfur
 */ 


#ifndef LEDS_H_
#define LEDS_H_

//LED pins
#define BLUE_PIN PD2
#define RED_PIN PD1
#define LIGHT_PIN PD6

//Functions
 void RED_on();
 void RED_off();
 void RED_toggle();
 void BLU_on();
 void BLU_off();
 void Light_ON();
 void Light_OFF();

#endif /* LEDS_H_ */