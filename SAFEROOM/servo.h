/*
 * servo.h
 *
 * Created: 10/30/2018 9:40:20 PM
 *  Author: rjfur
 */ 

#include <avr/io.h>
#ifndef SERVO_H_
#define SERVO_H_

#define Servo_Pin PB1

void T1pwm_Init(void);

void Servo_Open();

void Servo_Close();


#endif /* SERVO_H_ */