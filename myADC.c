#include "stm32f4xx.h"                  // Device header
#include "myADC.h"

#define V25 (float)0.76
#define AVG_SLOPE (float)0.0025

void TempConfig(void);
float Temp_Read(void);

void TempConfig(void)
{
	RCC->APB2ENR |=(1<<8);									//ADC-1 enabled
	ADC1->CR1 |=0x00000011;									// ADC analog input Channel16 for temp sensor Channel17 for VREFINT
//	ADC1->CR1 |=0x02000000;									//8-bit Resolution
	ADC1->SQR1 |=(0x00000000);
	ADC1->SQR3 |= 16;
	ADC1->SMPR1 |=0x00180000;								//144 cycles implemented for sampling
	ADC->CCR 		|=(1<<23);									//Temperature sensor and V REFINT channel enabled

	ADC1->CR2 |= (1<<10);										//The EOC bit is set at the end of each regular conversion. Overrun detection is enabled.
	
}

float Temp_Read(void)
{
	float Temp;
	ADC1->CR2		|=(1<<0);										//ADC1 enabled
	ADC1->CR2 |=(1<<30);										// Starts conversion of regular channels 
	for(int j=0; j<1000; j++);							// Unspecified delay
	
	while (!ADC_SR_EOC);										// Wait until conversion ends
	
	Temp =  (ADC1->DR*3.3/4095-V25)/AVG_SLOPE+25;
	
	ADC1->CR2 &=~ADC_CR2_ADON;							//ADC1 Disabled
	ADC1->SR =0x00;													//All status registers and flag reset
	return Temp;
}
