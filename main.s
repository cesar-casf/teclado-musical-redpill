RCC_APB2ENR EQU 0x40021018

GPIOA_CRL	EQU 0x40010800
GPIOA_CRH	EQU 0x40010804
GPIOA_IDR	EQU 0x40010808
GPIOA_ODR	EQU 0x4001080C

	EXPORT __main
	AREA MAIN , CODE , READONLY
__main
		LDR R1 ,= RCC_APB2ENR
		LDR R0 ,[R1] ; read the APB2ENR
		ORR R0 , R0 ,#0xFC ; enable the clocks for GPIOs
		STR R0 ,[R1] ; write R0 to APB2ENR

		LDR R1 ,= GPIOA_CRL
		LDR R0 ,=0x33333333
		STR R0 ,[R1] ; PA0 to PA7 as outputs

		LDR R1 ,= GPIOA_CRH
		LDR R0 ,=0x33333333
		STR R0 ,[R1] ; PA8 to PA15 as outputs

LOOP
		LDR R1 ,= GPIOA_ODR
		LDR R0 ,=0x0000 ; ODR = 0x0000 ( all pins low )
		STR R0 ,[R1]
		BL delay
		LDR R1 ,= GPIOA_ODR
		LDR R0 ,= 0x0001
		STR R0 ,[R1]
		BL delay
		LDR R1 ,= GPIOA_ODR
		LDR R0 ,= 0x0002
		STR R0 ,[R1]
		BL delay
		LDR R1 ,= GPIOA_ODR
		LDR R0 ,= 0x0004
		STR R0 ,[R1]
		BL delay
		BL delay
		LDR R1 ,= GPIOA_ODR
		LDR R0 ,= 0x8000
		STR R0 ,[R1]
		BL delay
		LDR R1 ,= GPIOA_ODR
		LDR R0 ,= 0x0100
		STR R0 ,[R1]
		BL delay
		LDR R1 ,= GPIOA_ODR
		LDR R0 ,= 0x0040
		STR R0 ,[R1]
		BL delay
		LDR R1 ,= GPIOA_ODR
		LDR R0 ,= 0x0020
		STR R0 ,[R1]
		BL delay
		LDR R1 ,= GPIOA_ODR
		LDR R0 ,= 0x0800
		STR R0 ,[R1]
		BL delay
		B LOOP
delay
		LDR R0 ,= 48 ; R0 = 48 , modify for different delays
d_L1 	LDR R1 ,= 250000 ; R1 = 250 , 000 ( inner loop count )
d_L2 	SUBS R1,R1,#1
		BNE d_L2
		SUBS R0 , R0 ,#1
		BNE d_L1
		BX LR
		END