/*
 * ADC.h
 *
 * Created: 11/26/2018 6:25:16 PM
 *  Author: rjfur
 */ 


#ifndef ADC_H_
#define ADC_H_

volatile uint16_t settemp_val;
volatile uint16_t IRresult1;
volatile uint16_t IRresult2;

//functions
void ADC_Init(uint8_t chan);

void ADC_Stop(void);

void ADC_SingleRead();

void ADC_Read(uint8_t select);

#endif /* ADC_H_ */