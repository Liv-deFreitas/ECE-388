/*
* SAFEROOM.c
*
* * Author : rjfur
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FSM.h"
#include "LCD.h"
#include "LCD2.h"
#include "DHT11.h"
#include "LEDs.h"
#include "Fans.h"
#include "Buttons.h"
#include "Climate_Control.h"
#include "ADC.h"
#include "PIR.h"
#include "servo.h"
#include "Solenoid.h"
#include "Keypad.h"

//#define Password_Length 5

int main(void)
{
	int8_t temp = 0;
	int8_t humid = 0;
	Button_setup();
	SOL_Setup();
	LCD_Init();
	LCD2_Init();
	char DHTDATA[100] ; //print buffer
	Potentio_setup();
	PIR_Setup();
	ADC_Read(1);//potentiometer
	T1pwm_Init();//servo
	//Keypad_Init();// keypadd
	STATE_Current = DORMANT; //DOORLOCK;
	LCD_Clear();
	LCD2_Clear();
	
	//Password Reader
	/*char pass_set[Password_Length] = "1234";
	char pass_data[Password_Length];
	uint8_t data_count = 0;
	char customkey;*/
	
	//*************Enable interrupts*****************
	//HC state button interrupt
	PCMSK0 |= (1<<PCINT0);
	PCICR |= (1<<PCIE0);
	
	//DR state button interrupt
	PCMSK2 |=(1<<PCINT23);
	PCICR |=(1<<PCIE2);
	
	//Keypad Interrupt
	//PCMSK0 |= (1<<PCINT1);
	//PCICR |= (1<<PCIE0);
	
	//potentiometer interrupt
	//PCMSK1 |= (1<<PCINT11);
	//PCICR |= (1<<PCIE1);
	
	sei();
	//********************************************

	while (1)
	{
		switch(STATE_Current)
		{
			case DORMANT:
			//LCD_Clear();
			break;
			case DOORLOCK:
			{
			Door_States();
			if (DRstate == 1)
			{
				Open_Door();
			}
			
			if (DRstate == 2)
			{
				_delay_ms(2000);
				Close_Door();
				LCD_Clear();
				STATE_Transition(CLIMATECONTROL);
			}
			break;
			
			}
			//*/
			
			case CLIMATECONTROL:
			LCD2_Clear();
			Room_Light();
			//Climate Control display temp set with potent::
			//TFan_on();
			//POT_Read();
			//	if(set)
			//	POT_Disp();
			//	GetSet_Disp();
			//***************************************
			//Buttons.c to change CLIMATE MODE::
			HC_states();
			//**********************************************
			
			_delay_ms(1500);// wait 1.5s
			DHT_GetTH(&temp, &humid);// get temp/humid values
			//Fan_State = 1;
			
			Fan_Control();
			if (DHT_GetTH(&temp, &humid) != -1) //check if error retrieving
			{
				
				//Print Temp data C
				LCD_Posit(0,0);
				itoa(temp,DHTDATA,10); //convert int val to string
				LCD_Print("TEM:");
				LCD_Print(DHTDATA);
				LCD_Print("C ");
				//LCD_Print(); //print degree symb

				//Print Temp data F
				DHT_CtoF(&temp);
				itoa(temp,DHTDATA,10);
				LCD_Print(DHTDATA);
				LCD_Print("F");
				
				//Print Humidity
				LCD_Posit(0,1);
				itoa(humid,DHTDATA,10);
				LCD_Print("HUM:");
				LCD_Print(DHTDATA);
				LCD_Print("%");
				//Fan_State = 1;
				//Fan_Control();
			}
			else
			{
				DHT_Error();
			}
			
			
			if (DRstate == 1)
				{
				LCD_Clear();
				LCD_Posit(4,0);
				LCD_Print("DOOR OPEN");
				Open_Door();
				_delay_ms(3000);
				LCD_Clear();
				STATE_Transition(DORMANT);
			}
			
			break;
		}
	}
	return 0;
}
