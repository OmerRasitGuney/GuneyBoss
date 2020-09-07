#include "stm32f4xx.h"                  // Device header
#include "GPIOConfig.h"



void GPIOConfig(void);

void GPIOConfig(void)
{
	RCC->AHB1ENR |= (1 << 0);				//GPIOA enabled
	RCC->AHB1ENR |= (1 << 3);				//GPIOD enabled
  GPIOD->MODER |= (0x2 << 24);   	// pin 12 af mode 10
  GPIOA->MODER &= 0xFFFFFFFC; 	  // Reset bits 0-1 to clear old values
  GPIOA->MODER |= 0x00000000; 	  // Make button an input
	GPIOD->MODER |= 0x54000000;			// PIN13,PIN14 and PIN15 set as output
	
	// Choose Timer4 as Alternative Function for pin 12 led
    GPIOD->AFR[1] |= (0x2 << 16);
	
}
