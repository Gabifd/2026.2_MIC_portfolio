/*
 * main.c
 *
 * Created: 11/12/2026 10:17:00 AM
 *  Author: Gabrieli Felipon
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"


void ADC_config(){
	ADMUX = (0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0)			//Canal de conversão: pino ADC0
	|(1<<REFS1)|(1<<REFS0);									//Referencia de tensão interna (1.1V)
	ADCSRA= (1<<ADEN)|(0<<ADATE)							//Habilita o ADC em modo "manual"
	| (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);						//Fator de prescale 128 (125Khz frequencia do ADC)
	DIDR0 = (1<<ADC0D);										//Desabilita a porta PC0 (função digital do pino ADC0)
}

int main(void){
	DDRB |= (1<<DDB0);
	ADC_config();
	_delay_ms(1);
    while(1){
		ADCSRA |= (1<<ADSC);								//Inicia uma conversão
		while((ADCSRA & (1<<ADSC)) != 0);
		//while((ADCSRA & (1<<ADIF)) == 0);
		uint16_t tADCData= ADC;								//Acesso ao ADCH e ADCL como um unico registrador de bits 16, faixa de inteiros de 0 a 1023 (ADLAR=0)
		if (tADCData < 670) {
			PORTB|= (1<<PORTB0); //Acender LED abaio de 720mV
		} else {
			PORTB &= ~(1<<PORTB0);
		}
	}
}