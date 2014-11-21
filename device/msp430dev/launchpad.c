#include<msp430g2553.h>
#include<string.h>
#include "launchpad.h"

int TCount123123[NUM_COUNT];
int TLimit[NUM_COUNT];

/**
 * @brief Desable Watchdog
 * @details Call to desable the Whatchdog
 */
void desabWDT()
{
	WDTCTL = WDTPW|WDTHOLD;
}

/**
 * @brief Enable the button
 * @details Enable the button without the interruption support
 */
void botao()
{
	P1DIR &= ~BOTAO;
	P1OUT |= BOTAO;
	P1REN |= BOTAO;	
}

/**
 * @brief Enable LED
 * @details Enable LED *n*, making this port a output port
 * 
 * @param numled LED to be enabled. Can assume the values:
 * 	+	LED1
 * 	+	LED2
 */
void hled(unsigned char numled)
{
	/*numled é LED1 ou LED2 */
	P1DIR|=numled;		
}

/* sensibilidade ao botão */
char readbotao(void)
{
	unsigned volatile sig;
	if ((P1IN & BOTAO) == BOTAO)
		sig = 1;
	else
		sig = 0;
		
	return sig;
			
}

/* Esperar equanto botão não/é pressionao */
void waitbton(unsigned char sinal)
{
	if (sinal==SOLTA)
		while(!readbotao())
		{}
	else if (sinal == APERTA)
		while(readbotao())
		{}
}

/* Acender led */
void ligled(char numled)
{
	P1OUT |= numled;
}

/* Apagar led */
void desled(char numled)
{
	P1OUT &= ~numled;
}

/* Alternar led */
void alterled(unsigned volatile numled)
{
	P1OUT ^= numled;
}

/* delay coxa! -- count 1000 */
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

/* configurar clock em 1MHz */
void dco1mhz()
{
	/* BASEADO EM EXEMPLOS	 */
	
	DCOCTL = 0;                             
	BCSCTL1 = CALBC1_1MHZ;                  
	DCOCTL = CALDCO_1MHZ;
}

/**
 * @brief Configure UART
 * @details Configure UART with 9600 baud rate
 * \f$UCA0BR_{value}= \frac{Frequency}{Rate_{desired}} \f$
 * 
 * To a Baud Rate = 9600 and 1MHz as clock we have:
 * \f$\frac{1\cdot 10^6}{9600} = 104,166 \f$
 * 
 * So:
 * + UCA0BR1 = 0;
 * + UCA0BR0 = 104;
 * + Error = 1.6%
 * 
 * [Source](http:/*www.win.tue.nl/~johanl/educ/RTcourse/MSP430%20UART.pdf)
 */
void hserial()
{
	P1SEL |= PIN_TX + PIN_RX ;                     /* P1.1 = RXD, P1.2=TXD */
	P1SEL2 |= PIN_TX + PIN_RX ;                    /* P1.1 = RXD, P1.2=TXD */
  
	UCA0CTL1 |= UCSSEL_2;                     /* SMCLK */
	UCA0BR0 = 104;                            /* 1MHz 9600 */
	UCA0BR1 = 0;                              /* 1MHz 9600 */
	UCA0MCTL = UCBRS0;                        /* Modulation UCBRSx = 1 */
	UCA0CTL1 &= ~UCSWRST;                     /* **Initialize USCI state machine** */
}

/* le um char da uart */
char getchar()
{
	//while(!(IFG2&UCA0RXIFG));
	return UCA0RXBUF;
	dly_coxa(1);
}

int putchar(int caracter)
{
	while (!(IFG2&UCA0TXIFG));
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

void setMultitimes()
{
	#define ATIVAR_TIMER
	CCTL0 = CCIE;                             // CCR0 interrupt enabled
	CCR0 = T_100US; 
	TACTL = TASSEL_2 + MC_1;                  // SMCLK, contmode
}

void setDigitalOut1(unsigned char pin)
{
	//numled é LED1 ou LED2
	P1DIR|=pin;		
}

void setPWMpin(PWM_PD *pwm_pin, unsigned char pin, int ntimer, int period)
{
	pwm_pin->pin = pin;
	pwm_pin->ntimer = ntimer;
	TLimit[ntimer] = period;
	//P1OUT |= VERD;
	
	#define ATIVA_PWM
}

#ifdef ATIVAR_TIMER
#pragma vector=TIMER0_A0_VECTOR
__interrupt void teste_timer1(void)
{
	int count;
	for(count = 0; count < NUM_COUNT; count++)         // Add Offset to CCR0
	{
		if(TCount[count] >= TLimit[count])
			TCount[count] = 0;
		else
			TCount[count]++;
	}
	
	/*if(TCount[1] <= TLimit[1]/2)
			ligled(VERD);
		else
<<<<<<< HEAD
			desled(VERD);*/
#ifdef ATIVA_PWM
	pwmOut(pwm0, fat);
#endif

	//contTacom();
/*=======
			desled(VERD);*/
	
// >>>>>>> cc74678dc9965719486786cbc2244dfe9c8330f4
	//P1OUT ^= VERD;
	
	GTacom.contL++;
	/*if(GTacom.contL> MAX_INT)
	{
		GTacom.contL = 0;
		}*/
		
	 contTacom();
	
	CCR0 = T_100US;
	CCTL0 &= ~CCIFG;
	LPM0_EXIT;
	
}
#endif



void pwmOut(PWM_PD pwm_pin, int upto)
{
	//volatile int comp = upto*TLimit[pwm_pin.ntimer]/100;
	
	if(TCount[pwm_pin.ntimer] <= upto)
		ligled(pwm_pin.pin);
	else
		desled(pwm_pin.pin);
}


void set_diginput()
{
	P1DIR &= ~BIT3;
	P1OUT |= BIT3;
	P1REN |= BIT3;
	P1IES |= BIT3;	
	P1IE |= BIT3;
}
       
 #pragma vector=PORT1_VECTOR     // Começa aqui a rotina de interrupção na Porta 1 (Com o LPM4 todos os clocks estão desligados)    
         __interrupt void Port_1_ISR(void)
{           
           // while(1)                                      // Loop Infinito
              //{
               //if ((P1IN & BIT5)==0)                 // Se  botão S1 está em 0
    
                P1OUT ^= BIT0;
                
                calc_vel();
               // GTacom.contL++;
               		                     //Acende Led 1 (Vermelho)
         //            else 
     // {
                 //P1OUT &= ~BIT0;                  //Apaga Led 1 (Vermelho)
                 P1IFG &= ~BIT3;                   // Reseta a flag(0)
       //         }
                //}
LPM0_EXIT;
}

void contTacom()
{
	
	if(GTacom.contL>= MAX_INT)
	{
		GTacom.contL = 0;
		GTacom.contM++;
	}
	
	if(GTacom.contM>= MAX_INT)
	{
		GTacom.contM = MAX_INT;
		GTacom.contL = MAX_INT;
	}	
}

void calc_vel()
{
	velocidade = '0'+9/((unsigned char) ((int) 9*(GTacom.contL+MAX_INT*GTacom.contM)/(MAX_INT + MAX_INT*MAX_INT)));
	GTacom.contL = 0;
	GTacom.contM = 0;
	
}
