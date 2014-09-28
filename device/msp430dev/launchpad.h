#ifndef _H_LAUNCHPAD
#define _H_LAUNCHPAD

/* defines do botão s2 da launchpad */
#define BOTAO BIT3
#define APERTA 1
#define SOLTA 0

/* defines do led */
#define LED1 BIT0
#define LED2 BIT6

#define VERM BIT0
#define VERD BIT6

#define ALTO 1
#define BAIXO 0

/* defines serial uart */
#define PIN_TX BIT1
#define PIN_RX BIT2

//<<<<<<< HEAD
// defines timer
#define T_100US 100 /* 100us period*/
#define NUM_COUNT 10	

//=======
#include <stdio.h>
#include "adc.h"	
//>>>>>>> ba77d88a5df4e5eb8f02948ffb69751eea2dfb1b

/* Counter timer A0 */
int TCount[NUM_COUNT];
int TLimit[NUM_COUNT];
/* PWM pin Descriptor */
typedef struct pwd_pd
{
	unsigned char pin;
	int ntimer;
} PWM_PD;

/* Desabilita WDT */
extern
void desabWDT();

/* habilita botão sem interrupção */
extern
void botao();

/* habilitar led n */
extern
void hled(unsigned char numled);

/* sensibilidade ao botão */
extern
char readbotao();

/* Esperar equanto botão não/é pressionado */
extern
void waitbton(unsigned char sinal);

/* Acender led */
extern
void ligled(char numled);

/* Apagar led */
extern
void desled(char numled);

/* Alternar led */
extern
void alterled(unsigned volatile numled);

/* delay coxa! -- count 1000  */
extern
void dly_coxa(int numcic);

/* configurar clock em 1MHz */
extern
void dco1mhz();

extern
void hserial();

/* le um char da uart */
extern
char getchar();

extern
int putchar(int caracter);

extern
void wsserial(char *st);

void setMultitimes();

void setDigitalOut1(unsigned char pin);



#endif

