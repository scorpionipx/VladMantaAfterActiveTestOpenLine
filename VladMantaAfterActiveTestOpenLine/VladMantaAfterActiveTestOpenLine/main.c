/*
 * VladMantaAfterActiveTestOpenLine.c
 *
 * Created: 21-Nov-17 7:45:21 PM
 * Author : ScorpionIPX
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define INPUT_PIN PINB0
#define OUTPUT PINB1
#define INPUT (PINB & 1)
#define SET_OUTPUT (PORTB |= 2)
#define RESET_OUTPUT (PORTB &= 1)
#define COUNTER_TOLERANCE 20


void init_uc(void);

unsigned int counter = 0;
unsigned int max_counter = 0;

void get_max_val_of_counter();

int main(void)
{
    /* Replace with your application code */
	init_uc();
	_delay_ms(100);
	get_max_val_of_counter(10000);
	max_counter -= COUNTER_TOLERANCE;
	
    while (1) 
    {
		_delay_us(200);
		if(INPUT)
		{
			counter ++;
			//SET_OUTPUT;
		}
		else
		{
			if(counter >= max_counter)
			{
				SET_OUTPUT;
				_delay_us(500);
			}
			counter = 0;
			RESET_OUTPUT;
		}
    }
}

void init_uc(void)
{
	DDRB = 0x00;
	DDRB |= 1 << OUTPUT;
	
	PORTB = 0x00;
}

void get_max_val_of_counter(int filter_rank)
{
	while(filter_rank --)
	{
		_delay_us(200);
		if(INPUT)
		{
			counter ++;
			//SET_OUTPUT;
		}
		else
		{
			if(counter > max_counter)
			{
				max_counter = counter;
			}
			counter = 0;
		}
	}
}