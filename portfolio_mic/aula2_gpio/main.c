/*
 * main.c
 *
 * Created: 8/27/2026 8:29:27 AM
 *  Author: Gabrieli Diel
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
#include "stdint.h"

//controle de varios leds com operações de shift

void GPIO_config() {
	DDRB = (1<<DDB6)|(1<<DDB4)|(1<<DDB2)|(1<<DDB0); //bits pares sao configurados com
	//DDRB = 0b01010101;
	//se são entradas, têm alta impedância
}

int main(void) {
	GPIO_config();
	uint8_t tData = 0x03; //0b0000 0011
	while (1) {
		PORTB = tData;
		//descobrir o DDB e o PORTB para saber o que vai acontecer efetivamente
		_delay_ms(1000);
		tData = tData << 1 ; //0b0000 0110, 0b0000 1100, 0b0001 1000, ...
		if (tData == 0){
			tData = 0x03;
		}
	}
}