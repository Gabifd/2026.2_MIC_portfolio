/*
* aula8_spi.cpp
*
* Created: 08/10/2026 08:49:04
* Author : Gabrieli Felipon
*/

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"


int main(void){
	SPI_master_config();
	while (1){
		_delay_ms(1);
	}
}
