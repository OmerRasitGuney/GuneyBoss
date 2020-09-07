#include "stm32f4xx.h"                  // Device header
#include "myUSART.h"
#include <string.h>
#include <stdio.h>

char ReadByte;
char ReadData[20];
uint8_t DataCnt;

void USARTConfig(void);
void USART_Transmit_Data(char *Data);


void USARTConfig(void)
{

	RCC->APB1ENR |=(1<<17);											//USART2 clock enabled
//	RCC->AHB1ENR |= (1 << 0);
	// set pin modes as alternate mode 7 (pins 2 and 3)
	// USART2 TX and RX pins are PA2 and PA3 respectively
	GPIOA->MODER &= ~(0xFU << 4); // Reset bits 4:5 for PA2 and 6:7 for PA3
	GPIOA->MODER |=  (0xAU << 4); // Set   bits 4:5 for PA2 and 6:7 for PA3 to alternate mode (10)

	// set pin modes as high speed
	GPIOA->OSPEEDR |= 0x000000A0; // Set pin 2/3 to high speed mode (0b10)

	// choose AF7 for USART2 in Alternate Function registers
	GPIOA->AFR[0] |= (0x7 << 8); // for pin A2
	GPIOA->AFR[0] |= (0x7 << 12); // for pin A3	

//	USART2->CR1 |= (0<<12);											//1 Start bit, 8 Data bits, n Stop bit
//	USART2->CR2 |= (0x00<<12);									//1 Stop bit as default
	
	//--->Baudrate Calculatiton according to RM0090<----
	// tx/rx baud = fclk / (8 * (2-OVER8) * USARTDIV) 
	//As default our oversampling mode by so OVER8 reg = 0 as a default, fclk = 16MHz
	// For 115200KBps baud rate USARTDIV => (16*10^6) / ( 8*(2-0)*115200) ==> 8,68055
	//According to table in RM0090 Value programmed in the baud rate register 8.6875 set,
	//So USARTDIV = 8,6875 selected ==> Then, MANTISSA(USARTDIV) = 8 anc because of oversampling by 16 
	//FRACTION(USARTDIV) = 16*0.6875 = 11; 
	
	USART2->CR1 |= (1<<3);											//Transmitter is enabled
	USART2->CR1 |= (1<<2);											//Receiver is enabled
	USART2->CR1 |= (1<<5);											//An USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register
	USART2->BRR |= (8<<4);											//MANTISSA(USARTDIV) = 8
	USART2->BRR |= (11);											//FRACTION(USARTDIV) = 16*0.6875 = 11; 

	NVIC_SetPriority(USART2_IRQn,3);
	NVIC_EnableIRQ(USART2_IRQn);
	
	USART2->CR1 |= (1<<13);											//USART2 ENABLED
	
}

void USART_Transmit_Data(char *Data)
{
		for(int i=0;i<strlen(Data);i++)
	{
		USART2->DR = Data[i];
		while(!(USART2->SR & (1 << 6)));
	}
	
	for(int i=0; i<5000000; i++);
}

void USART2_IRQHandler(void)
{
	if(USART2->SR & (1<<5))
		ReadData[DataCnt]=USART2->DR;
	if(USART2->DR=='\0')
	{
		
		memset(ReadData,0,strlen(ReadData));
		DataCnt=0;
	}
	else DataCnt++;
	
}

