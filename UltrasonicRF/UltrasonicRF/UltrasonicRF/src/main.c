/**
 * Ultrasonic RF
 *
 * Liv de Freitas
 *
 */

/**
	Help from: http://avrprogramer.blogspot.com/2014/01/obstacle-detection-using-ultrasonic.html
			   https://stackoverflow.com/questions/12738672/c-volatile-keyword-in-isr-and-multithreaded-program
			   https://community.atmel.com/projects/distance-measurement-using-atmega328p-and-hc-sr04
 */

#define F_CPU 8000000UL
#define SPEED_OF_SOUND 34300
#include <asf.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

volatile float tmp=0;
volatile float dist=0;
volatile uint16_t time1=0;
volatile uint16_t time2=0;
volatile uint16_t timercounter=0;


void InitADC();
void send_trig();
uint16_t ReadADC(uint16_t ADCchannel);

void InitADC()//initialize ADC
{
	ADMUX = (0b00 << REFS0);// Select Vref=AREF
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);//set prescaler to 128 so we have a 125Khz clock source and enable ADC
}


void IO_Init()//initialize port IO
{
	DDRC |= (1<<DDC6);//makes pc6 an output (trig)
	DDRD |= (1<<DDD1);//makes pd1 an output (LED)
	DDRC &= (0<<DDC3);//makes pc3 an input (echo)
}


void power_led()
{
	PORTD|=(1<<PORTD1);//turns on LED
}

void led_off()
{
	PORTD&=(0<<PORTD1);//turns off LED
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	IO_Init();
	//InitADC();
	MCUCR&=(0<<ISC11);//enable interrupt on rising edge
	MCUCR|=(1<<ISC10);//enable interrupt on falling edge
	EIMSK |= (1<<INT1);//turns on INT1
	TIMSK0 |= (1<<TOIE0);//enable timer interrupts
	sei();//enable all interrupts
	
	while(1)
	{
		if(running==0)
		{
			_delay_ms(60);
			send_trig();
		}
	}

	/* Insert application code here, after the board has been initialized. */
}

uint16_t ReadADC(uint16_t ADCchannel)//Read ADC value
{
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);//select ADC channel with mask
	ADCSRA |= (1<<ADSC);//enter conversion mode
	while( ADCSRA & (1<<ADSC) )	;// wait until ADC conversion is complete
	return ADC;//return ADC value
}
ISR(TIMER0_OVF_vect)//from link above
{
	if (up)
	timercounter++;
}
SIGNAL(INT1_vect)//from link above
{
	if(running)
	{
		if(!up)
		{
			up=1;
			timercounter=0;
			TCCR0B &=(0<<CS02);
			TCCR0B &=(0<<CS01);
			TCCR0B |=(1<<CS00);
			TCNT0=0;
		}
		else
		{
			up=0;
			dist=(timercounter*256+TCNT0)/58;//gives distance in cm
			running=0;
			if (dist==5)//if door is 5cm away, it is closed. Light LED
			{
				power_led();
			}
			else
			{
				led_off();
			}
		}
	}
}

void send_trig()//from link above
{
	PORTD=0x00;
	_delay_us(5);
	PORTD=0xF0;
	running=1;
	_delay_us(10);
	PORTD=0x00;
}