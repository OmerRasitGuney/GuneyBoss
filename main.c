#include "stm32f4xx.h"                  // Device header
#include "sysClockConfig.h"							// Sets the system clock 16MHz
#include "myADC.h"											// includes Temp measurement configurations
#include "myPWM.h"											// includes PWM configurations
#include "myUSART.h"										// includes USART configurations
#include "EXTIConfig.h"									// includes basic External interrupt configurations
#include "GPIOConfig.h"									// includes basic GPIO configurations
#include <math.h>
#include <string.h>
#include <stdio.h>

float Temp;
char msg[20]="Hello World\n\r";
extern char ReadData[20];
char res[20];

void Init_Periphs(void);
float Temp_Read(void);
void USART_Transmit_Data(char *Data);

int main(void)
{

Init_Periphs();													// Initializes the peripherals
	
while(1)
{
USART_Transmit_Data((char *)msg);				// Transmitting msg

Temp=Temp_Read();												// Writes temp data 
strcpy(res,ReadData);										// attains USART Receiving data to res
		
}	
}



void Init_Periphs(void)
{
	SysConfig();
	GPIOConfig();
	EXTIConfig();
	TempConfig();
	TimConfig();
	USARTConfig();
	
}

