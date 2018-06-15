#include "stm8s.h"
#include "stdio.h"

/* Private function prototypes -----------------------------------------------*/
static void UART1_Init(void);
static void CLK_Init(void);
static void GPIO_Init();
static void AWU_Init();

#define LED (1 << 3)

void main(void)
{
	disableInterrupts();
	GPIO_Init();
	AWU_Init();
	CLK_Init();
	UART1_Init();
	enableInterrupts();

	while(1)
	{
		halt();
		
		#ifdef DEBUG
			printf("Hello!");
		#endif
	}
}

void GPIO_Init()
{
	GPIOD->DDR |= LED;
	GPIOD->CR1 |= LED;
	GPIOD->ODR &= ~LED;  
}

void AWU_Init()
{
	AWU->CSR &= ~AWU_CSR_AWUEN;
	AWU->TBR |= 0x0D; // 2s
	AWU->APR |= 0x3E; // 2s
	AWU->CSR |= AWU_CSR_AWUEN;
}


void CLK_Init()
{
	CLK->CKDIVR = 0x00; // 16 Mhz
	CLK->PCKENR1 |= CLK_PCKENR1_UART1;
}

void UART1_Init()
{
	UART1->BRR2 = 0x03; // 9600 baud
	UART1->BRR1 = 0x68;
	UART1->CR1 = 0x00;
	UART1->CR2 = UART1_CR2_RIEN | UART1_CR2_REN | UART1_CR2_TEN; // enable RX interrupt, enable rx, tx
}

int putchar(int c)
{
	UART1->DR = (uint8_t)c;
	while (!(UART1->SR & UART1_SR_TXE));

	return c;
}



INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18) // UART1 rx handler
{

}

INTERRUPT_HANDLER(AWU_IRQHandler, 1)
{
	if (AWU->CSR & 0x20)
	{
		GPIOD->ODR ^= LED;
	}
} 
