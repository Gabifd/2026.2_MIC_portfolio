/*
 * main.c
 *
 * Created: 9/24/2026 10:20:37 AM
 *  Author: Gabrieli Felipon
 */ 

#define F_CPU 16000000
#include <xc.h>
#include <string.h>
#include "util/delay.h"
#include "avr/interrupt.h"

#define RX_BUFFER_SIZE 16

uint8_t gMessage[16];								//buffer global da uart
uint16_t gRxCounter = 0;							//contagem de bytes recebidos
uint8_t gMessageReady = 0;

/**
* Configuração do modulo USART0 para modo assincrono, frame de 8 bits, paridade par
**/


void UART_config_rx(uint16_t pBAUD){
	UCSR0A = (0<<U2X0);								//MODO DOUBLE SPEED DESATIVADO
	UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(0<<UCSZ02)		//Habilita o receptor UART0, frame de 8 bits
	| (1<<RXCIE0);									//Habilita interrumpção da recepção da UART0
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)				//modo assíncrono
	|(1<<UPM01)|(0<<UPM00)							//Habilita paridade par
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
		  gMessage[gRxCounter] = tReceivedByte;		//armazena bytes recebidos no buffer
		  gRxCounter++;
		  if(gRxCounter == RX_BUFFER_SIZE) {//Proteção contra estouro do buffer
		  gRxCounter = 0;
		  }
		  if(tReceivedByte == '\n'){
			  gMessageReady = 1;					//Flag de mensagem completa
		  }
}

int main(void) {
	GPIO_config();
	UART_config_rx(9600);
	sei();												//habilta interrupções globalmente
    while(1) {
		if(gMessageReady){								//aguarda mensagem completa
			gMessageReady = 0;
		
		//Tratamento da mensagem recebida
if(strcmp((char*)gMessage, "Message") == 0){
	PORTC |= (1<<PORTC0);					//LED VERDE
	} else {
	PORTC |= (1<<PORTC1);						//LED VERMELHO
}
_delay_ms(10);
PORTC = 0;									//Apaga todos os LEDs
}
}
}