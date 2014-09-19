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

// defines timer
#define T_100US 100 /* 100us period*/
	

// Desabilita WDT
void desabWDT();

// habilita botão sem interrupção
void botao();

// habilitar led n
void hled(unsigned char numled);

// sensibilidade ao botão
char readbotao();

// Esperar equanto botão não/é pressionao
void waitbton(unsigned char sinal);

// Acender led
void ligled(char numled);

// Apagar led
void desled(char numled);

// Alternar led
void alterled(unsigned volatile numled);

// delay coxa! -- count 1000
void dly_coxa(int numcic);

// configurar clock em 1MHz
void dco1mhz();

void hserial();

//le um char da uart
char getchar();

int putchar(int caracter);

void wsserial(char *st);

void setMultitimes();

#endif

