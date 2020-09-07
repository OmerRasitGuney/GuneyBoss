#include "stm32f4xx.h"                  // Device header
#include "sysClockConfig.h"


void SysConfig(void);

void SysConfig(void)
{
	
	FLASH->ACR =
            FLASH_ACR_LATENCY_5WS               /* 6 CPU cycle wait */
          | FLASH_ACR_PRFTEN                    /* enable prefetch */
          | FLASH_ACR_ICEN                      /* instruction cache enable */
          | FLASH_ACR_DCEN;                     /* data cache enable */
	
	RCC->CFGR |= 0x00000090;	// HCLK system clock divided by 4
	/* Clock control register */
		RCC->CR = RCC_CR_HSEON;         /* Enable external oscillator */

		/* Wait for locked external oscillator */
		while((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);
	
	//f (VCO clock) = f (PLL clock input) × (PLLN / PLLM) ==> 8 * (64 / 4) = 128MHz
	//f (PLL general clock output) = f (VCO clock) / PLLP ==> 128 / 2 		 = 64MHz
	
	RCC->PLLCFGR =
          RCC_PLLCFGR_PLLSRC_HSE                /* PLL source */
        | (4 << 0)                              /* PLLM input division */
        | (64 << 6)                          	  /* PLLN multiplication */
        | (0 << 16)                             /* PLLP sys clock division */
        | (7 << 24);                            /* PLLQ usb clock division =48MHz */

	
	// As you can see above, the SystemClock set 64MHz
	// By dividing the SystemClock 4, HCLK will set 16MHz
	
/* Enable PLL */
RCC->CR |= RCC_CR_PLLON;


/* Wait for locked PLL */
while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

/* select system clock */
RCC->CFGR &= ~RCC_CFGR_SW; /* clear */
RCC->CFGR |= RCC_CFGR_SW_PLL;   /* SYSCLK is PLL */

/* Wait for SYSCLK to be PPL */
while((RCC->CFGR & RCC_CFGR_SW_PLL) != RCC_CFGR_SW_PLL);
}
