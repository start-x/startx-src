#ifndef _H_LAUNCHPAD
#define _H_LAUNCHPAD

// defines do botão s2 da launchpad
#define BOTAO BIT3
#define APERTA 1
#define SOLTA 0

// defines do led
#define LED1 BIT0
#define LED2 BIT6

#define VERM BIT0
#define VERD BIT6

#define ALTO 1
#define BAIXO 0

// defines serial uart
#define PIN_TX BIT1
#define PIN_RX BIT2

#include <stdio.h>
#include <adc.h>	

// Desabilita WDT
extern
void desabWDT();

// habilita botão sem interrupção
extern
void botao();

// habilitar led n
extern
void hled(unsigned char numled);

// sensibilidade ao botão
extern
char readbotao();

// Esperar equanto botão não/é pressionao
extern
void waitbton(unsigned char sinal);

// Acender led
extern
void ligled(char numled);

// Apagar led
extern
void desled(char numled);

// Alternar led
extern
void alterled(unsigned volatile numled);

// delay coxa! -- count 1000
extern
void dly_coxa(int numcic);

// configurar clock em 1MHz
extern
void dco1mhz();

extern
void hserial();

//le um char da uart
extern
char getchar();

extern
int putchar(int caracter);

extern
void wsserial(char *st);

#endif

