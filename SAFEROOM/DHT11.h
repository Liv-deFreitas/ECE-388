/*
* DHT11.h
*
* Created: 11/11/2018 10:22:39 PM
*  Author: rjfur
*/

#include <stdio.h>
#include <avr/io.h>
#ifndef DHT11_H_
#define DHT11_H_

#define DHT11_PIN 5//Define DHT11 PIN

//timeout retries
#define DHT_TIMEOUT 200

//get temp f value


//functions
int8_t DHT11_Getdata( int8_t *temp, int8_t *humid);

int8_t DHT_GetTH(int8_t *temp, int8_t *humid);

int8_t DHT_CtoF(int8_t *temp);

int8_t DHT_GetTemp(int8_t *temp);

int8_t DHT_GetHumid(int8_t *humid);

void DHT_Error();

void DHT_Timerset();
#endif /* DHT11_H_ */