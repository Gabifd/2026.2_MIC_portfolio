/*
 * sm28vlt32.c
 *
 * Created: 08/10/2026 10:41:52
 *  Author: Gabrieli Felipon
 */ 

#include "spi.h"

void SM28VLT_config(){
		DDRC = (1<<DDC0);		//USANDO PC0 COMO SLAVE SELECT (SAIDA)
		PORTC |= (1<<PORTC0);				//
}

uint8_t SM28VLT_readword(uint32_t pAddress) {
	uint8_t tAddressByte2 = (pAddress & 0x00FF0000) >> 16;
	uint8_t tAddressByte1 = (pAddress & 0x0000FF00) >> 08;
	uint8_t tAddressByte0 = (pAddress & 0x00FF00FF);
	uint8_t tDataByte1;
	uint8_t tDataByte0;
	uint16_t tDataWord;
	
	PORTC &= ~(1<<PORTC0);						//Slave select em nivel baixo
	SPI_transceive(0x15);						//Comando "Read word"
	SPI_transceive(tAddressByte2);
	SPI_transceive(tAddressByte1);
	SPI_transceive(tAddressByte0);
	tDataByte1 = SPI_transceive(0x00);
	tDataByte0 = SPI_transceive(0x00);
	SPI_transceive(0x00);						//Dummy
	PORTC |= (1<<PORTC0);						//SLAVE SELECT EM NIVEL ALTO	
	tDataWord= ((uint16_t) tDataByte1) << 08
						|((uint16_t) tDataByte0) << 00;
	return tDataWord;
}
