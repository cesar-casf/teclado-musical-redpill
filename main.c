#include "stm32f10x.h"
#include "const.h"
#include "lcd.h"

void potenciometro(void);
void va_prescaler(uint16_t psc);
void timbre_val(void);
uint16_t calculo_psc(uint16_t freq);

#define BitTst(arg,bit) ((arg) & (1<<bit))		//Testa se um BIT está setado


static uint32_t ADCvalue;

int main()
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; //Configura clock para I/O alternado 
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE; //Desabilita interface JTAG 
	RCC->APB2ENR |= 0xFC|(1<<9)|(1<<14); //Configura o clock das GPIO //pot: ADC1 clock, usart1
	RCC->APB1ENR |= (1<<1); // Habilita clock do TIMER3
	
	GPIOB->CRH = 0x44444444; //Configura as chaves como input
	GPIOB->CRL = 0x4444440B; //Configura as outras chaves como input e o buzzer como output
	GPIOA->CRL = 0x43344333; //Configura PA7/PA4/PA3 como input e as demais como saida
	GPIOA->CRH = 0x33333333; //Configura o LCD como output
	GPIOC->CRH = 0x44444444;
	
	//Config potenciometro
	ADC1->CR2 = 1;
	ADC1->SMPR2 = 1<<27;
	delay_us(1);
	
  //Config PWM1
  TIM3->CCMR2 = 0x0060; //Configura modo PWM1
	TIM3->ARR = 36 - 1; //ARR = 35
	
    //I LCD
    lcd_init();
	
	//Inicia na oitava 1
	unsigned char oitava = 1;
	lcd_command(0x80);
	lcd_print("Oitava: 1");	

	//Inicia o timbre com ciclo = 25%
	lcd_command(0xC0);
	lcd_print("Ciclo: 25%");
	TIM3->CCR3 = 9;

	while(1)
	{
		//Enquanto a Oitava 2 esta selecionada
		while(oitava==1)
		{
			//Verifica a selecao da oitava 2
			if(!BitTst(GPIOB->IDR,13)) 
			{
				lcd_command(0x80);
				lcd_print("Oitava: 2");//print no lcd
				oitava = 2;//altera a oitava
			}					
			//Verifica a selecao de timbre(ciclo)
			if(!BitTst(GPIOB->IDR,14)){timbre_val();} 
			//Testa qual tecla foi pressionada
			//Reproduz a nota respectiva a tecla enquanto pressionada
			while(!BitTst(GPIOB->IDR,5)) {
				va_prescaler(calculo_psc(C));
			} 
			while(!BitTst(GPIOB->IDR,10)) {
				va_prescaler(calculo_psc(C_sustenido));
			} 
			while(!BitTst(GPIOB->IDR,4)) {
				va_prescaler(calculo_psc(D));
			}
			while(!BitTst(GPIOA->IDR,7)) {
				va_prescaler(calculo_psc(D_sustenido));
			}
			while(!BitTst(GPIOB->IDR,3)) {
				va_prescaler(calculo_psc(E));
			}
			while(!BitTst(GPIOA->IDR,3)) {
				va_prescaler(calculo_psc(F));
			}
			while(!BitTst(GPIOC->IDR,15)) {
				va_prescaler(calculo_psc(F_sustenido));
			}
			while(!BitTst(GPIOA->IDR,4)) {
				va_prescaler(calculo_psc(G));
			}
			while(!BitTst(GPIOC->IDR,14)) {
				va_prescaler(calculo_psc(G_sustenido));
			}
			while(!BitTst(GPIOB->IDR,8)) {
				va_prescaler(calculo_psc(A));
			}
			while(!BitTst(GPIOC->IDR,13)) {
				va_prescaler(calculo_psc(A_sustenido));
			}
			while(!BitTst(GPIOB->IDR,9)) {
				va_prescaler(calculo_psc(B));
			}
			while(!BitTst(GPIOB->IDR,11)) {
				va_prescaler(calculo_psc(C_2));
			}
			
			//Para a reprodução ao soltar a tecla
			TIM3->CCER = 0;
			TIM3->CR1 = 0;			
		}
		//Enquanto a Oitava 2 esta selecionada
		while(oitava==2)
		{
			//Verifica a selecao da oitava 1
			if(!BitTst(GPIOB->IDR,12))
			{
				lcd_command(0x80);
				lcd_print("Oitava: 1");//print no lcd
				oitava = 1;//altera a oitava
			}
			//Verifica a selecao de timbre(ciclo)
			if(!BitTst(GPIOB->IDR,14)){timbre_val();} 
			//Testa qual tecla foi pressionada
			//Reproduz a nota respectiva a tecla enquanto pressionada
			while(!BitTst(GPIOB->IDR,5)) {
				va_prescaler(calculo_psc(C_2));
			}   
			while(!BitTst(GPIOB->IDR,10)) {
				va_prescaler(calculo_psc(C_sustenido_2));
			} 
			while(!BitTst(GPIOB->IDR,4)) {
				va_prescaler(calculo_psc(D_2));
			}
			while(!BitTst(GPIOA->IDR,7)) {
				va_prescaler(calculo_psc(D_sustenido_2));
			}
			while(!BitTst(GPIOB->IDR,3)) {
				va_prescaler(calculo_psc(E_2));
			}
			while(!BitTst(GPIOA->IDR,3)) {
				va_prescaler(calculo_psc(F_2));
			}
			while(!BitTst(GPIOC->IDR,15)) {
				va_prescaler(calculo_psc(F_sustenido_2));
			}
			while(!BitTst(GPIOA->IDR,4)) {
				va_prescaler(calculo_psc(G_2));
			}
			while(!BitTst(GPIOC->IDR,14)) {
				va_prescaler(calculo_psc(G_sustenido_2));
			}
			while(!BitTst(GPIOB->IDR,8)) {
				va_prescaler(calculo_psc(A_2));
			}
			while(!BitTst(GPIOC->IDR,13)) {
				va_prescaler(calculo_psc(A_sustenido_2));
			}
			while(!BitTst(GPIOB->IDR,9)) {
				va_prescaler(calculo_psc(B_2));
			}
			while(!BitTst(GPIOB->IDR,11)) {
				va_prescaler(calculo_psc(C_3));
			}
			
			//Para a reprodução ao soltar a tecla
			TIM3->CCER = 0;
			TIM3->CR1 = 0;
		}	
	}
}


//Verificacao do valor do potenciometro para variação de frequencia
void potenciometro(void)
{
	ADC1->SQR3 = 9;
	ADC1->CR2 = 1;
	while((ADC1->SR&(1<<1)) == 0);
	ADCvalue = ADC1->DR;
}


void va_prescaler(uint16_t psc)
{	
	potenciometro();								//pot() para a nota pressionada
	TIM3->CCER |= (1 << 8); 			//Ativa o canal 3
	TIM3->PSC = psc - ADCvalue / 7;		    // Seta o prescaler
	TIM3->CR1 = 1;						// Aciona o TIMER3
	delay_ms (100);
}

void timbre_val(void){	
	lcd_command(0xC0);
	//verifica o timbre atual e altera para o proximo valor
	switch(TIM3->CCR3)	{
		case 27: 	//Caso 75% -> 25%
			lcd_print("Ciclo: 25%");
			TIM3->CCR3 = 9;
			break;
		case 9: 	//Caso 25% -> 50%
			lcd_print("Ciclo: 50%");
			TIM3->CCR3 = 18;
			break;
		case 18: 	//Caso 50% -> 75%
			lcd_print("Ciclo: 75%");
			TIM3->CCR3 = 27;			
			break;
	}	
	delay_ms (100);												
}		

//calcula o valor de PSC-1 com base na freq[Hz] da nota desejada
uint16_t calculo_psc(uint16_t freq){
	return (2000000/(2*freq))-1;
}