/*
 * main.c
 *
 * Created: 8/27/2026 8:29:27 AM
 *  Author: Gabrieli Diel
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

#define BIT0_MASK 0b00000001
#define BIT1_MASK 0b00000010
#define BIT2_MASK 0b00000100
#define BIT5_MASK 0b00100000

int main(void){
	//3 formas diferentes de setar a direção de PB2 e PB5
	DDRB = (1<<DDB5) | (1<<DDB2);
	DDRB = 0b00100000 | 0b00000100;
	//res 0b00100100
	
	DDRB = BIT5_MASK | BIT2_MASK;
    while(1)
    {
        //TODO:: Please write your application code 
    }
}