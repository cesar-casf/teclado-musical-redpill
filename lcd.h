#ifndef LCD_H
#define LCD_H

#include <stm32f10x.h>
#include "delay.h"

#define LCD_RS 15
#define LCD_EN 12

void lcd_init(void);
void lcd_print (char *str);
void lcd_command (unsigned char cmd);
void lcd_data (unsigned char data);
void lcd_putValue (unsigned char value);

void lcd_init()
{
	delay_ms (15);
	GPIOA->ODR &= ~(1 << LCD_EN); // LCD_EN = 0
	delay_ms (3); // delay de 3 ms 
	lcd_command (0x33); //lcd init .
	delay_ms (5);
	lcd_command (0x32); //lcd init .
	delay_us (3000);
	lcd_command (0x28); //4 - bit mode , seta 1 linha and 5x8 caracteres 
	delay_ms (3);
	lcd_command (0x0E); //liga o display e o cursor
	delay_ms (3);
	lcd_command (0x01); //limpa o display
	delay_ms (3);
	lcd_command (0x06); //move para a direita
	delay_ms (3);
}

void lcd_putValue (unsigned char value)
{
	uint16_t aux ; //variavel auxiliar para os dados de saida
	aux = 0x0000 ; //limpa a aux
	GPIOA->BRR = (1 << 5)|(1 << 6)|(1 << 8)|(1 << 11); // limpa as linhas
	aux = value & 0xF0 ;
	aux = aux >> 4;
	GPIOA->BSRR = ((aux & 0x0008) << 8) | ((aux & 0x0004) << 3) | ((aux & 0x0002 ) << 5) | (( aux & 0x0001 ) << 8);
	GPIOA->ODR |= (1 << LCD_EN ); /* EN = 1 for H - to - L pulse */
	delay_ms (3); /* make EN pulse wider */
	GPIOA->ODR &= ~(1 << LCD_EN ); /* EN = 0 for H - to - L pulse */
	delay_ms (1); /* wait */
	GPIOA->BRR = (1 << 5)|(1 << 6)|(1 << 8)|(1 << 11); // limpa as linhas
	aux = 0x0000; // clear aux
	aux = value & 0x0F;
	GPIOA->BSRR = ((aux & 0x0008) << 8) | ((aux & 0x0004) << 3) | ((aux & 0x0002) << 5) | ((aux & 0x0001) << 8);
	GPIOA-> ODR |= (1 << LCD_EN ); /* EN = 1 for H - to - L pulse */
	delay_ms (3); /* deixa o pulso EN mais amplo */
	GPIOA->ODR &= ~(1 <<LCD_EN ); /* EN = 0 for H - to - L pulse */
	delay_ms (1); /* wait */
}

void lcd_command (unsigned char cmd)
{
	GPIOA -> ODR &= ~(1 <<LCD_RS); /* RS = 0 para comando */
	lcd_putValue (cmd);
}

void lcd_data (unsigned char data)
{
	GPIOA->ODR |= (1 << LCD_RS ); /* RS = 1 para dados */
	lcd_putValue (data);
}

void lcd_print (char *str)
{
	unsigned char i = 0;
	while (str[i] != 0) /* enquanto não for o fim da string */
	{
		lcd_data (str[i]); /* mostra a str[i] no LCD */
		i++;
	}
}
#endif