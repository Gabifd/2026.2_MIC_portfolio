/*
 * main.c
 *
 * Created: 9/17/2026 10:15:10 AM
 *  Author: Gabrieli Felipon
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

char gMessage[16] = "Mensagem";	//Null terminated string, (precisa dos x caracteres da mensagem + 1 bit nulo, nesse caso: 8 +1 terminação nula) dessa forma o micro sabe que a mensagem acabou 

/**
* Configuração do modulo USART0 para modo assincrono, frame de 8 bits, paridade par, BAUD de 9600
**/                                                             


void UART_config(){
	UCSR0A = (0<<U2X0); //MODO DOUBLE SPEED DESATUIVADO
	UCSR0B = (0<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02); //Habilita o transmissor UART0, frame de 8 bots
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)	//modo assíncrono
	|(1<<UPM01)|(1<<UPM00)	//Habilita paridade par
	|(1<<USBS0) //2 bits de stop
	|(1<<UCSZ01)|(1<<UCSZ00) //Frame de 8 bits
	|(0<<UCPOL0);  //polaridade clock: ignorada
	UBRR0= 103; //BAUD de 9600, erro de 0,16%
}

/**
* Envia um byte na USART0                                                                     
**/


void UART_send_byte(uint8_t pByte){
	//Aguardar espaço no buffer (semáforo)
	while((UCSR0A & (1<<UDRE0)) == 0);
	UDR0 = pByte;	//Envia um byte parâmetro
}

void UART_send_string(char * pString) {
	char *tMessagePtr = pString;	// * indica que é um ponteiro
	UART_send_byte(*tMessagePtr);	// * e Ptr desreferencia(pega a primeira letra dela)
	while(*tMessagePtr != 0){
	tMessagePtr++;					// incrementa o ponteiro, fzendo com que leia a proxima letra
	UART_send_byte(*tMessagePtr);
	}
	UART_send_byte('\n');	//desreferencia a proxima letra 
	}

int main(void){
	UART_config();
    while(1){
		UART_send_string(gMessage);
        //UART_send_byte('M');	//M
		//UART_send_byte(0x49);	//I
		//UART_send_byte(0x43);	//C
		//UART_send_byte('\n');	//Line feed (0x0A)
		_delay_ms(5); //Tempo de silêncio
    }
}