#include "stm32f4xx.h"                  // Device header
#include "myDAC.h"

void DACConfig(void);

void DACConfig(void)
{
	RCC->APB1ENR |=(1<<29);								// DAC interface clock enabled from RCC
	
	RCC->AHB1ENR |= (1 << 0);

  GPIOA->MODER &= 0xFFFFFCFF; // Reset bits 8-9 to clear old values
  GPIOA->MODER |= 0x00000300; // Set pin 4 to analog mode (0b11)
	
	DAC1->CR |= (1<<0);										// DAC1 CH1 ENABLED
	DAC1->CR |= (0<<1);										// DAC1 output buffer disabled
	
	DAC1->DHR12R1 = 2048;									// VDD/2 loaded to DAC channel1 12-bit right-aligned data holding register
	DAC1->CR |= (7<<3);										// Software trigger set as DAC channel1 trigger selection
	DAC1->CR |= (1<<2);										// DAC channel1 trigger enabled
}
