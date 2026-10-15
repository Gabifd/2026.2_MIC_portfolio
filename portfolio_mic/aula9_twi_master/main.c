/*
 * main.c
 *
 * Created: 10/15/2026 8:59:13 AM
 *  Author: Gabrieli Felipon
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void TWI_master_config(){
	TWBR = 64;									//Divisor 64, fscl=100kHz
	TWSR |= (0<<TWPS1)|(0<<TWPS0);				//Prescaler de 1
	TWCR |= (1<<TWEN);							//HABILITA O PERIFÉRICO
}




int main(void){
	TWI_master_config();
	_delay_ms(1000);
	uint8_t tSlaveAddress =10;
    while(1){
												//Iniciar uma transmissão como mestre
	TWCR|=(1<<TWSTA);							//Inicia condição de start
	while((TWCR & (1<<TWINT)) == 0);				//Aguarda flag de interrupção subir
	uint8_t tStatusCode = (TWSR & 0b11111000);
	if(tStatusCode== 0x08){							//Condição de start ok?
												//Iniciar escrita  10
		TWDR = (tSlaveAddress<<1)|0;
		TWCR = (1<< TWINT)|(1<<TWEN);
		while((TWCR & (1<<TWINT))== 0)
		tStatusCode = (TWSR & 0b11111000);
		if(tStatusCode == 0x18){
			//ack recebido
		}else
			if(tStatusCode==0x28){
							//Nack recebido (ou ack não recebido)
			}else{
}												//algum erro...
					}else{
				//outro erro}
									
	TWCR|= (1<<TWINT);							//Limpar flag de interrupção
		}
	_delay_ms(100);
 
	}
}
 