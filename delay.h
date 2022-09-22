#ifndef DELAY_H
#define DELAY_H

#include <stm32f10x.h>
void delay_ms(uint16_t t);
void delay_us(uint16_t t);

void delay_ms(uint16_t t){
	volatile unsigned long l = 0;
	for (uint16_t i = 0; i < t ; i ++){
		for ( l = 0; l < 6000; l ++);
	}
}

void delay_us(uint16_t t){
	volatile unsigned long l = 0;
	for (uint16_t i = 0; i < t ; i ++){
		for ( l = 0; l < 6; l ++);
	}
}

#endif
