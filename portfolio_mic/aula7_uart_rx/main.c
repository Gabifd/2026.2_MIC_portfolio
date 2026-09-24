/*
 * main.c
 *
 * Created: 9/24/2026 10:20:37 AM
 *  Author: Gabrieli Felipon
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
#include "avr/interrupt.h"
/**
* Configuração do modulo USART0 para modo assincrono, frame de 8 bits, paridade par
**/


void UART_config_rx(uint16_t pBAUD){
	UCSR0A = (0<<U2X0);								//MODO DOUBLE SPEED DESATIVADO
	UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(0<<UCSZ02)		//Habilita o receptor UART0, frame de 8 bits
	| (1<<RXCIE0);									//Habilita interrumpção da recepção da UART0
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)				//modo assíncrono
	|(1<<UPM01)|(1<<UPM00)							//Habilita paridade par
	|(1<<USBS0)										//2 bits de stop
	|(1<<UCSZ01)|(1<<UCSZ00)						//Frame de 8 bits
	|(0<<UCPOL0);									//polaridade clock: ignorada
	UBRR0 = (1000000 / pBAUD) -1;					
}
void GPIO_config(){
	DDRC = (1<<DDC0)|(1<<DDC1);					//PC0 E PC1	COMO SAÍDA
}

ISR(USART_RX_vect){
	       uint8_t tReceivedByte = UDR0;				//Leitura do buffer UART
	       //Tratamento da mensagem recebida
	       if(tReceivedByte == 'M'){
		       PORTC |= (1<<PORTC0);					//LED VERDE
		       } else {
		       PORTC |= (1<<PORTC1);						//LED VERMELHO
	       }
	       _delay_ms(1);
	       PORTC = 0;									//Apaga todos os LEDs
}

int main(void) {
	GPIO_config();
	UART_config_rx(9600);
	sei();												//habilta interrupções globalmente
    while(1) {
//
	}
}