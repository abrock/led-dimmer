/*
 * vim:ts=4:sw=4:expandtab
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#define BAUD 9600
#include <util/delay.h>
#include <stdio.h>
#include "adc.h"

#include "lookup.h"

#define mydelay(delay) {uint16_t _mydelay_del = delay; while(_mydelay_del--){_delay_us(10);}}

int main() {

	ADC_Init();

	uint16_t delay = 512;

	DDRB = 0b11111011;
	DDRC = 0b11011111;
	DDRD = 0b00000000;

	for(;;) {
		ADC_start(5);

		PORTB = 0xff;
		PORTC = 0b11011111;
		PORTD = 0xff;
		
		mydelay(1024-delay);
		
		PORTB = 0x00;
		PORTC = 0x00;
		PORTD = 0x00;

		mydelay(delay);

		delay = lookup[ADC_result()/3];
	}
}
