/*
 * spi.c
 *
 * Created: 08/10/2026 10:34:16
 *  Author: Gabrieli Felipon
 */ 

#include <xc.h>
void SPI_master_config(){
	SPCR = (1<<SPE)|(1<<DORD)		//Habilita SPI, ordem MSB primeiro (padrão)
	|(1<<MSTR)						//Modo Mestre
	|(0<<CPOL)|(0<<CPHA)			//SPImodo 0
	|(0<<SPR1)|(0<<SPR0);			//Divisor fosc/2 SCK->8MHz
	SPSR = (1<<SPI2X);				//Velocidade dobrada
	//DDRB = (1<<DDB3)|(1<<DDB5);		//Configura os pinos MDS1 e SCK como saida
	//DDRC = (1<<DDC0);				//Usando PC0 como Slave Select (saida)
}

uint8_t SPI_transceive(uint8_t pTxByte) {
	uint8_t tReceivedByte;
	PORTC &= ~(1<<PORTC0);			//Slave select nivel baixo
	SPDR =0xC7;						//Escrita do SPDR	dispara a transação
	while((SPSR & (1<<SPIF)) == 0);	//Espera a flag SPIF subir
	tReceivedByte = SPDR;			// Leitura do registrador de dados
	PORTC|= (1<<PORTC0);			//Slave select em nivel baixo
	return tReceivedByte;
}