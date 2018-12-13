/*
 * IRsensor.h
 *
 * Created: 10/30/2018 2:03:34 AM
 *  Author: rjfur
 */ 

#include <avr/io.h>
#ifndef IRSENSOR_H_
#define IRSENSOR_H_

volatile uint16_t Myresult; //My ADC value 10-bits

void ADC_Init(void);
void T0_Init(void);
void ADC_Stop(void);

#endif /* IRSENSOR_H_ */