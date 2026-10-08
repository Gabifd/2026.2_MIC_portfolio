/*
 * aula8_spi.cpp
 *
 * Created: 08/10/2026 08:49:04
 * Author : Gabrieli Felipon
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"


void SPI_master_config(){
	SPCR = (1<<SPE)|(1<<DORD)		//Habilita SPI, ordem MSB primeiro (padrão)
	|(1<<MSTR)						//Modo Mestre
	|(0<<CPOL)|(0<<CPHA)			//SPImodo 0
	|(0<<SPR1)|(0<<SPR0);			//Divisor fosc/2 SCK->8MHz
	SPSR = (1<<SPI2X);				//Velocidade dobrada
	DDRB = (1<<DDB3)|(1<<DDB5);	//Configura os pinos MDS1 e SCK como saida
}


int main(void){
	SPI_master_config();
    while (1){
		SPDR = 0xC7;
		_delay_ms(1);
    }
}

