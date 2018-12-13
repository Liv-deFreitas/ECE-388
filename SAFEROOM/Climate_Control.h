/*
 * Climate_Control.h
 *
 *
 *  Author: rjfur
 */ 


#ifndef Climate_Control_H_
#define Climate_Control_H_

#define Pot_PIN PC3
volatile uint16_t setvalue;
volatile uint8_t maxval;
volatile uint8_t minval;

void Potentio_setup();

void POT_Read();

void POT_Disp();

void POT_Divider();

void GetSet_Disp();

void Temp_AUTO();

void POT_CLEAR();

#endif /* Climate_Control_H_ */