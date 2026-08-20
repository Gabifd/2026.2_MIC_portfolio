/*
 * main.c
 *
 * Created: 8/20/2026 8:59:00 AM
 *  Author: Gabi
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

int main(void)
{
	DDRB|= 0b00100000; //define pino PB5 como saida
    while(1)
    {
		PORTB |= 0b00100000; //ATRIBUI NIVEL LOGICO ALTO AO PINO pb5
		_delay_ms(100);
		PORTB &= 0b11011111;
		_delay_ms(900); //atribui nivel logico baixo ao pino pb5
        //TODO:: Please write your application code 
    }
}