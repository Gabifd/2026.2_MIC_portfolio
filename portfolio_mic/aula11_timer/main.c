/*
 * main.c
 *
 * Created: 10/22/2026 10:51:01 AM
 *  Author: Gabrieli Felipon
 */ 

#include <xc.h>
#include "avr/interrupt.h"

//Objetivo: obter uma interrupção com periodo de 10ms

ISR(TIMER0_COMPA_vect){		//Interupção de comparação A do timer 0
	PORTB ^= (1<<PORTB0);
}


void TMR0_config(){
	TCCR0A = (1<<WGM01)|(0<<WGM00);		//Configuração no modo CTC
	TCCR0B = (0<<WGM02)|(1<<CS02)|(0<<CS01)|(1<<CS00);
	OCR0A = 155;						//Corresponde a 9,984ms
	TIMSK0 =(1<<OCIE0A);				//Habilita interrupção COMPA
}

int main(void){
	DDRB |= (1<<DDB0);					//PORTB0 COMO SAIDA
	TMR0_config();
	sei();
    while(1){
        //TODO:: Please write your application code 
    }
}