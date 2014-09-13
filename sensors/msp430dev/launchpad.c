#include<msp430g2553.h>
#include<string.h>
#include "launchpad.h"

// Desabilita WDT
void desabWDT()
{
	WDTCTL = WDTPW|WDTHOLD;
}

// habilita botão sem interrupção
void botao()
{
	P1DIR &= ~BOTAO;
	P1OUT |= BOTAO;
	P1REN |= BOTAO;	
}
// habilitar led n
void hled(unsigned char numled)
{
	//numled é LED1 ou LED2
	P1DIR|=numled;		
}
// sensibilidade ao botão
char readbotao()
{
	unsigned volatile sig;
	if ((P1IN & BOTAO) == BOTAO)
		sig = 1;
	else
		sig = 0;
		
	return sig;
			
}

// Esperar equanto botão não/é pressionao
void waitbton(unsigned char sinal)
{
	if (sinal==SOLTA)
		while(!readbotao())
		{}
	else if (sinal == APERTA)
		while(readbotao())
		{}
}

// Acender led
void ligled(char numled)
{
	P1OUT |= numled;
}

// Apagar led
void desled(char numled)
{
	P1OUT &= ~numled;
}

// Alternar led
void alterled(unsigned volatile numled)
{
	P1OUT ^= numled;
}

// delay coxa! -- count 1000
void dly_coxa(int numcic)
{
	volatile unsigned int count1 = 0, count2 = 0;
	
	for (count1 = 0; count1< numcic; count1++)
	{
		for(count2 = 0; count2 < 1000; count2++)
		{
		}
	}
}

// configurar clock em 1MHz
void dco1mhz()
{
	// BASEADO EM EXEMPLOS	
	
	DCOCTL = 0;                             
	BCSCTL1 = CALBC1_1MHZ;                  
	DCOCTL = CALDCO_1MHZ;
}

void hserial()
{
	P1SEL |= PIN_TX + PIN_RX ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= PIN_TX + PIN_RX ;                    // P1.1 = RXD, P1.2=TXD
  
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 104;                            // 1MHz 9600
	UCA0BR1 = 0;                              // 1MHz 9600
	UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

//le um char da uart
char getchar()
{
	return UCA0RXBUF;
}

int putchar(int caracter)
{
	UCA0TXBUF = caracter;
	
	return 0;
}

void wsserial(char *st)
{
	volatile int cont = 0, len = strlen(st);
	
	for(cont=0; cont<len; cont++)
		{
			putchar(st[cont]);
			dly_coxa(1);
		}
}


