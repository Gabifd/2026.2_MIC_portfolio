/*
* aula8_spi.cpp
*
* Created: 08/10/2026 08:49:04
* Author : Gabrieli Felipon
*/

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
#include "spi.h"
#include "sm28vtl32.h"


int main(void){
	SPI_master_config();
	SM28VLT32_config();
	while (1){
		uint8_t tMemoryData = SM28VLT32_readWord(1000);
		_delay_ms(1);
	}
}
