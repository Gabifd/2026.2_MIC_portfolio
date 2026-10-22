/*
 * main.c
 *
 * Created: 10/22/2026 8:27:43 AM
 *  Author: Gabrieli Felipon
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

ISR(TWI_vect){
	PORTB |= (1<<PORTB0);
	//Tratar o estado atual da maquina do TWI
	uint8_t tStatusCode = (TWSR & 0b11111000);
	switch(tStatusCode){
		case(0x60): {						//Recebido SLA+W inicio da escrita do mestre
			PORTB |= (1<<PORTB1);
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);	//Envio do ACK
		} break;
		
		case(0x80): {		
			PORTB |= (1<<PORTB2);				//Novo dado recebido do mestre
			uint8_t tReceivedByte = TWDR;	//Recebe o dado enviado pelo mestre
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);	//Envio do ACK	
		} break;
		case(0xA0): {						//Final de transmissão(stop condition ou repeated start)
			PORTB |= (1<<PORTB3);
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT);
		} break;
		default: {
			PORTB |= (1<<PORTB4);
											//Algum erro ou condição não tratada
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT);
		}
	}
	
	TWCR = (1<<TWIE)|(1<<TWINT);
	_delay_ms(1);
	PORTB = 0;
}

void TWI_slave_config(uint8_t pAddress){
	TWBR = 64;									//Divisor 64, fscl=100kHz
	TWSR |= (0<<TWPS1)|(0<<TWPS0);				//Prescaler de 1
	TWCR |= (1<<TWEN)|(1<<TWIE)|(1<<TWINT);							//HABILITA O PERIFÉRICO
	TWAR = pAddress<<1;
	}

int main(void){
	DDRB|= (1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);		//SAIDAS PARA LEDS DE SINALIZAÇÃO
	TWI_slave_config(10);
	sei();
    while(1){
    }
}