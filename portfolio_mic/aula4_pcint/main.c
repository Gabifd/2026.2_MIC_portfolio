/*
 * main.c
 *
 * Created: 9/3/2026 8:56:47 AM
 *  Author: Gabrieli Diel
 */ 

#include <xc.h>
#include "avr/interrupt.h"

ISR(PCINT0_vect){
	
}

void GPIO_config{
	DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); //Define as portas PB0 PB1 PB2 PB3	 COMO ENTRADA- seta elas como 1, o << shifta a esquerda, ~inverte 0 pra 1 e 1 pra 0 e & multiplica a & a mascara pelo original, setando  1111 0000 (ja é originalmente assim, é apenas uma boa pratica)
	//DDRD = 0xff; //seta todos como saída, MESMO QUE 0b11111111
	DDRD |= (1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3)
			|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7)| //configura PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7 como saidas
	};


void PCINT_config(){
	
}

int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
    }
}