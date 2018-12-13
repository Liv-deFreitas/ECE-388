/*
* Fans.c
*
*
*  Author: rjfur
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "Fans.h"
#include "Climate_Control.h"
#include "Buttons.h"
#include "DHT11.h"
#include "LEDs.h"

//temp fan
void TFan_on()
{
	DDRB |= (1 << TFan_PIN); // Set TFan as output
	PORTB |= (1 << TFan_PIN); //Turn on TFan

};

void TFan_off()
{
	PORTB &= ~(1 << TFan_PIN); //Turn off TFan
};

//humidity fan
void HFan_on()
{
	DDRD |= (1 << HFan_PIN); // Set Hfan as output
	PORTD |= (1 << HFan_PIN); //Turn on Hfan
}

void HFan_off()
{
	PORTD &= ~(1 << HFan_PIN); //Turn off Hfan
}


void Fan_Control()
{
	//		setv = setvalue;
	int8_t temp = 0;
	int8_t humid = 0;
	
	DHT_GetTemp(&temp);
	DHT_GetHumid(&humid);
	
	switch (Fan_State)
	{
		//1 ******************AUTO**********************************
		case 1:
		{
			if (humid < 30.0)
			{
				HFan_on(); //if humidity fall below 30 turn on humidifier
			}
			Temp_AUTO();
			POT_CLEAR();
			//AUTO_state();
			if (((temp * 9.0)/ 5.0 + 32) > 75.0)
			{
				BLU_on();
				TFan_on();
			}
			
			else if (((temp * 9.0)/ 5.0 + 32) < 65.0)//
			//If temp < 55 turn on heat
			{
				LED_state = 2;
				RED_on();
				TFan_on();
			}
			
			else
			{
				BLU_off();
				RED_off();
				TFan_off();
			}
			break;
			
		}
		//2 ***************HEAT*********************************
		case 2:
		{
			//if (humid < 30.0)
			//{
				//HFan_on(); //if humidity fall below 30 turn on humidifier
			//}
			POT_Disp();
			GetSet_Disp();
			if (setvalue > ((temp * 9.0)/ 5.0 + 32))
			{
				TFan_on();
			}
			
			else if(setvalue < ((temp * 9.0)/ 5.0 + 32))//
			
			{
				TFan_off();
			}
			
			else
			{
				TFan_off();
			}
			break;
		}
		//3 **********************COOOL***********************************
		case 3:
		{
			//if (humid < 30.0)
			//{
			//HFan_on(); //if humidity fall below 30 turn on humidifier
			//}
			POT_Disp();
			GetSet_Disp();
			if (setvalue < ((temp * 9.0)/ 5.0 + 32))
			{
				TFan_on();
			}
			
			else if(setvalue > ((temp * 9.0)/ 5.0 + 32))//
			
			{
				TFan_off();
			}
			
			else
			{
				TFan_off();
			}
			break;
		}
		//3 **********************OFF*************************************
		case 4:
		{
			//Fan control OFF
			TFan_off();
			HFan_off();
			break;
		}
		//break;
		
		//default
		//default:

	}
}
//}