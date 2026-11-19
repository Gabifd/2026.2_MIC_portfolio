/*
 * main.c
 *
 * Created: 11/19/2026 8:33:40 AM
 *  Author: Gabrieli Felipon
 */ 

#include <xc.h>
#include "avr/interrupt.h"

uint16_t x[4];												//medidas do ADC

ISR(TIMER1_COMPB_vect){
	//PORTB ^= (1<<PORTB1);									//Para visualizar o tempo
}


ISR(ADC_vect){												//Interrupção referente a conversão concluida
	PORTB |= (1<<PORTB1);
	uint16_t tADCData = ADC;
		//Filtro media movel de ordem 4
		x[3] = x[2];										//Linha de atraso do sinal x (fila FIFO)
		x[2] = x[1];
		x[1] = x[0];
		x[0] = tADCData;
			uint16_t y = (x[0] +x[1] + x[2] +x[3]) / 4;		//Filtro media movel de ordem 4

	if (y < 670) {
		PORTB |=  (1<<PORTB0);								//
	}else{
				PORTB &= ~(1<<PORTB0);
			PORTB |= (1<<PORTB0);
		}
	}

void ADC_config(){
	ADMUX = (0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0)			//Canal de conversão: pino ADC0
	|(1<<REFS1)|(1<<REFS0);									//Referencia de tensão interna (1.1V)
	ADCSRA= (1<<ADEN)|(1<<ADATE)							//Habilita o ADC em modo "automatico"
	| (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)						//Fator de prescale 128 (125Khz frequencia do ADC)
	|(1<<ADIE);												//Habilita interrupção do AD
	DIDR0 = (1<<ADC0D);										//Desabilita a porta PC0 (função digital do pino ADC0)
	ADCSRB = (1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0);				//fONTE DO DISPARO: tmr1 cOMPARE MATCH b
}

//Configurar timer 1 para disparo a cada 1ms
void TMR1_config(){
	TCCR1A = (0<<WGM11)|(0<<WGM10);
	TCCR1B = (0<<WGM13)|(0<<WGM12)							//Modo 4: CTC com topo em OCR1A
			|(0<<CS12)|(0<<CS11)|(0<<CS10);					//Prescaler unitario
	OCR1A= 15999;									//Periodo de 1ms
	OCR1B=0;
	//TIMSK1 = (1<<OCIE1B);							//Debug:> habilita interrupção compare match B
}

int main(void){
	DDRB = (1<<DDB1)|(1<<DDB0);								//Pinos PB0 E PB1 como saidas
	TMR1_config();
	ADC_config();
	sei();
    while(1){
        //TODO:: Please write your application code 
    }
}