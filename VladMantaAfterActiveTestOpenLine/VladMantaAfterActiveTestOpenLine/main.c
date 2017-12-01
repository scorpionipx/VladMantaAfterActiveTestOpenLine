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
#define LOW 0
#define HIGH 1
#define SET_LED_A (PORTC |= 32)
#define CLEAR_LED_A (PORTC &= ~(32))
#define SET_LED_B (PORTC |= 2)
#define CLEAR_LED_B (PORTC &= ~(2))
#define SET_LED_C (PORTD |= 128)
#define CLEAR_LED_C (PORTD &= ~(128))
#define INIT_DELAY_MS 210
#define REF_A_CFG 0
#define REF_B_CFG 1
#define REF_C_CFG 2

<<<<<<< HEAD
#define CFG_REF_A_NUMBER_OF_RISING_EDGES 9
#define CFG_REF_B_NUMBER_OF_RISING_EDGES 3
#define CFG_REF_C_NUMBER_OF_RISING_EDGES 4
#define CFG_REF_A_DELAY_AFTER_LAST_PTP_MS 80
#define CFG_REF_B_DELAY_AFTER_LAST_PTP_MS 40
#define CFG_REF_C_DELAY_AFTER_LAST_PTP_MS 30
=======
#define RISING_EDGES 9
#define TIME_TO_WAIT_MS 92


>>>>>>> 9168e017875bf2fcefc28cf9305d66a4cf46e2a3

void init_uc(void);

unsigned int counter = 0;
unsigned int max_counter = 0;
unsigned short rising_edge = 0;
unsigned short level = LOW;

unsigned short cfg_number_of_rising_edges = 0;
unsigned short cfg_delay_after_last_psp_ms = 0;
unsigned short configuration = 0;

void get_max_val_of_counter();
void trigger(void);
void dynamic_delay_ms(unsigned int miliseconds);
void configuration_check(void);

int main(void)
{
    /* Replace with your application code */
	init_uc();
	_delay_ms(100);
	configuration_check();
	
	SET_LED_A;
	_delay_ms(50);
	
	while(bit_is_clear(PINC, 6))
	{
		if(!bit_is_clear(PINC, 7))
		{
			configuration ++;
			configuration %= 3;
			switch(configuration)
			{
				case REF_A_CFG:
				{
					CLEAR_LED_B;
					CLEAR_LED_C;
					SET_LED_A;
					break;
				}
				case REF_B_CFG:
				{
					CLEAR_LED_A;
					CLEAR_LED_C;
					SET_LED_B;
					break;
				}
				case REF_C_CFG:
				{
					CLEAR_LED_A;
					CLEAR_LED_B;
					SET_LED_C;
					break;
				}
				default:
				{
					break;
				}
			}
			_delay_ms(300);
		}
	}
	
	switch(configuration)
	{
		case REF_A_CFG:
		{
			cfg_delay_after_last_psp_ms = CFG_REF_A_DELAY_AFTER_LAST_PTP_MS;
			cfg_number_of_rising_edges = CFG_REF_A_NUMBER_OF_RISING_EDGES;
			break;
		}
		case REF_B_CFG:
		{
			cfg_delay_after_last_psp_ms = CFG_REF_B_DELAY_AFTER_LAST_PTP_MS;
			cfg_number_of_rising_edges = CFG_REF_B_NUMBER_OF_RISING_EDGES;
			break;
		}
		case REF_C_CFG:
		{
			cfg_delay_after_last_psp_ms = CFG_REF_C_DELAY_AFTER_LAST_PTP_MS;
			cfg_number_of_rising_edges = CFG_REF_C_NUMBER_OF_RISING_EDGES;
			break;
		}
		default:
		{
			break;
		}
	}
	
	SET_LED_A;
	SET_LED_B;
	SET_LED_C;
	
	get_max_val_of_counter(10000);
	max_counter -= COUNTER_TOLERANCE;
	
    while (1) 
    {
		_delay_us(200);
		if(INPUT)
		{
			if(level == LOW)
			{
				rising_edge ++;
				if(rising_edge >= cfg_number_of_rising_edges)
				{
					//_delay_ms(50);
					//SET_OUTPUT;
					//_delay_us(500);
					//RESET_OUTPUT;
<<<<<<< HEAD
					dynamic_delay_ms(cfg_delay_after_last_psp_ms);
=======
					_delay_ms(TIME_TO_WAIT_MS);
>>>>>>> 9168e017875bf2fcefc28cf9305d66a4cf46e2a3
					SET_OUTPUT;
					CLEAR_LED_A;
					CLEAR_LED_B;
					CLEAR_LED_C;
					//_delay_us(500);
					//RESET_OUTPUT;
				}
			}
			level = HIGH;
			counter ++;
			//SET_OUTPUT;
		}
		else
		{
			level = LOW;
			if(counter >= max_counter)
			{
				rising_edge = 0;
				//SET_OUTPUT;
				//_delay_us(500);
				//trigger();
				//SET_OUTPUT;
			}
			counter = 0;
			//RESET_OUTPUT;
		}
    }
}

void init_uc(void)
{
	DDRB = 0x00;
	DDRB |= 1 << OUTPUT;
	
	PORTB = 0x00;
	
	DDRC = 0b00111111;
	PORTC = 0x00;
	
	DDRD = 0b10000000;
	PORTD = 0x00;
}

void trigger(void)
{
	_delay_ms(10);
	SET_OUTPUT;
	_delay_us(500);
	RESET_OUTPUT;
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

void dynamic_delay_ms(unsigned int miliseconds)
{
	unsigned int counter;
	counter = miliseconds;
	while(counter --)
	{
		_delay_ms(1);
	}
}

void load_configuration(void)
{
	if(bit_is_clear(PINB, 2))
	{
		
	}
}

void configuration_check(void)
{
	SET_LED_A;
	_delay_ms(INIT_DELAY_MS);
	SET_LED_B;
	_delay_ms(INIT_DELAY_MS);
	SET_LED_C;
	_delay_ms(INIT_DELAY_MS);
	CLEAR_LED_A;
	_delay_ms(INIT_DELAY_MS);
	CLEAR_LED_B;
	_delay_ms(INIT_DELAY_MS);
	CLEAR_LED_C;
	_delay_ms(INIT_DELAY_MS);
	SET_LED_A;
	_delay_ms(INIT_DELAY_MS);
	SET_LED_B;
	_delay_ms(INIT_DELAY_MS);
	SET_LED_C;
	_delay_ms(INIT_DELAY_MS);
	CLEAR_LED_A;
	_delay_ms(INIT_DELAY_MS);
	CLEAR_LED_B;
	_delay_ms(INIT_DELAY_MS);
	CLEAR_LED_C;
	_delay_ms(INIT_DELAY_MS);
}