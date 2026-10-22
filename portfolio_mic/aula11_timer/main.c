/*
 * main.c
 *
 * Created: 10/22/2026 10:51:01 AM
 *  Author: Gabrieli Felipon
 */ 

#include <xc.h>
#include "avr/interrupt.h"

uint16_t gMilliseconds = 0;
uint8_t gClockSeconds = 0;
uint8_t gClockMinutes = 0;
uint8_t gClockHour = 0;
 
//Objetivo: obter uma interrupção com periodo de 10ms

ISR(TIMER0_COMPA_vect){		//Interupção de comparação A do timer 0
gMilliseconds += 10;
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
		
		if(gMilliseconds <100){
			PORTB |= (1<<PORTB0);		//Seta PB0 por 100ms
			} else{
			PORTB &= ~(1<<PORTB0);		//Zera PB0 por 900ms
		}
		
        //Logica do RTC (Real Time Clock)
			if(gMilliseconds >=1000){
				gMilliseconds -= 1000;
				gClockSeconds++ ;
				if(gClockSeconds >= 60){
					gClockSeconds = 0;
					gClockMinutes++;
					if(gClockMinutes >= 60){
						gClockMinutes=0;
						gClockHour++;
						if(gClockHour >=24){
							gClockHour=0;
						}
					}
				}
			} 
		}
	}
   
