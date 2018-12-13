/*
* DHT11_SENSOR.c
*
* Created: 11/20/2018 1:34:30 AM
*  Author: rjfur
https://bitbucket.org/arturmietek/avr-starter.git
Author: mentos
*/
#define F_CPU 16000000
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "DHT11_SENSOR.h"
#define TIMEOUT 10000
//return values
//0 : OK
//-1 : CS error
//-2 : timeout

uint8_t bits[5];
uint8_t i, j = 0;

int DHT11_Getdata(uint8_t select) {
	
	//convert and store
	humid = (bits[0]);  // bit[1] == 0;
	temp = (bits[2]);  // bits[3] == 0;

	//reset port
	//DDRD |= (1 << DHT11_PIN); //output
	//PORTD |= (1 << DHT11_PIN); //high
	//_delay_ms(100);

	//send request
	DDRD |= (1 << DHT11_PIN); //output
	PORTD &= ~(1 << DHT11_PIN); //low
	_delay_ms(20);
	PORTD |= (1 << DHT11_PIN); //high
	_delay_us(40);
	DDRD &= ~(1 << DHT11_PIN); //input
	//_delay_us(39);
	
	//Get response or timeout
	unsigned int loopCnt = TIMEOUT
	while((PORTD &= ~(1 << DHT11_PIN))) //while low
		if (loopCnt == 0){
			return -2; //timeout
		}
		loopCnt = TIMEOUT;
		while(PORTD |= (1 << DHT11_PIN)) //while high
		if (loopCnt == 0)
		{
			return -2;//timeout
		}

	//read the data
	for (j = 0; j < 5; j++) { //read 5 byte
		uint8_t result = 0;
		for (i = 0; i < 8; i++) { //read every bit
			while (!(PIND & (1 << DHT11_PIN)))
			; //wait for an high input
			_delay_us(30);
			if (PIND & (1 << DHT11_PIN)) //if input is high after 30 us, get result
			result |= (1 << (7 - i));
			while (PIND & (1 << DHT11_PIN))
			; //wait until input get low
		}
		bits[j] = result;
	}
	return 0

	//reset port
	//DDRD |= (1 << DHT11_PIN); //output
	//PORTD |= (1 << DHT11_PIN); //low
	//_delay_ms(100);

	//check checksum
	uint8_t sum;
	sum = (bits[0] + bits[2]);
	 {
		if (bits[4] != sum)
		{
		return -1;
		}
		else
		{
		return 0;
		}

