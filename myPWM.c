#include "stm32f4xx.h"                  // Device header
#include "myPWM.h"


void TimConfig(void);

void TimConfig(void)
{
	RCC->APB1ENR |= (1 << 2);		//TIM4 enabled
	
	//The counter clock frequency CK_CNT is equal to f CK_PSC / (PSC[15:0] + 1).
	TIM4->PSC = 7999;				// 16MHz / (7999+1) = 2kHz
	TIM4->ARR = 2000;				// PWM freq 2000/2000 = 1Hz so 1s 
	TIM4->CCR1 = 1000;				// Duty set as half of ARR, so in per 0.5s 
	TIM4->CCMR1 |= (0x6 << 4);		//  Output compare 1 mode set as PWM Mode 1
	TIM4->CCMR1 |= (1 << 3);			// Output compare 1 preload enabled
	
	//If TIM4 interrupt dont wanted using uncomment 2 rows below and close all tim4 interrupt codes
//	TIM4->CR1 |= (1<<7);					// Auto-reload preload enabled,TIMx_ARR register is buffered
//	TIM4->EGR |= (1<<0);				// Re-initialize the counter and generates an update of the registers. 
	TIM4->CCER |= (1 << 0);			// CC1 channel configured as output and OC1 signal is output on the corresponding output pin
	
	TIM4->DIER |=(1<<0);					//Update interrupt enabled
	
	NVIC_SetPriority(TIM4_IRQn,2);
	NVIC_EnableIRQ(TIM4_IRQn);
	TIM4->CR1 |= (1 << 0);
}

void TIM4_IRQHandler(void)
{
	
	// clear interrupt status
    if (TIM4->DIER & 0x01) {
        if (TIM4->SR & 0x01) {
					GPIOD->BSRR |=0x00001000;
            TIM4->SR &= ~(1U << 0);
        }
    }
	

}

