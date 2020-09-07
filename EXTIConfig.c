#include "stm32f4xx.h"                  // Device header
#include "EXTIConfig.h"

void EXTIConfig(void);


void EXTIConfig(void)
{
	RCC->APB2ENR |=(1<<14);		// SYSCFG is enabled :The system configuration controller is mainly used to remap the 
														// memory accessible in the code area, select the Ethernet PHY interface and manage 
														// the external interrupt line connection to the GPIOs.
	
	SYSCFG->EXTICR[0] |= 0x00000000;	// for EXTI0 configuration 
	
	EXTI->RTSR =0x00000001;		// For PA0 rising trigger enabled
	EXTI->IMR = 0x00000001;		// Interrupt request from line x is not masked
	
	NVIC_SetPriority(EXTI0_IRQn,1);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & (1<<0) )		// Check if the interrupt came from exti0
	{
			GPIOD->BSRR |=0x0000E000;	//PIN13,PIN14 and PIN15 set
		for(int j=0; j<1000000; j++);		
	}
	else
			GPIOD->BSRR |=0xE0000000;	//PIN13,PIN14 and PIN15 set 
	EXTI->PR = (1 << 0);			// Clear pending bit
	
}


