#include<msp430g2553.h>

#include "launchpad.h"
#include "Wrap.h"


int main()
{
	/* Counting parameters */
	volatile int counter = 0, endcount = 1000;
	char ch;	
	
	
	
	desabWDT();
	/* botao(); */
	dco1mhz();
	hserial();
	
	hled(VERM|VERD);
	//ligled(VERM);
	
	setPWMpin(&pwm0, VERM, 0, 600);
	setMultitimes();
	
	//TLimit[0] = 5000;
	
	TCount[0] = 0;
	
	TLimit[1] = 4000;
	
	TCount[1] = 0;
	
	fat = 1;
	
	//P1OUT ^= VERM;
	/* Defined in Wrap.h */
	int cmd;

	_BIS_SR(LPM0_bits+GIE);

	for(;;)
	{
		//P1OUT ^= VERM;
		//ligled(VERM);
		
		//desled(VERM);
		cmd = getchar();
		switch(cmd)
		{
			case ALL_VALUES:
				//printf("[%d,%d]\n", adc_read(0),adc_read(1));
				break;
			case 'a':
			case BREAK_MSP:
			
				//dly_coxa(1000);
				while(!(IFG2&UCA0RXIFG));
				ch = getchar();
								
				if((ch >= '0') && (ch <= '9'))
					fat = 1 + (int) ((unsigned char) ch-'0');
				putchar(ch);
					//if(counter >= endcount)
					//{
						//counter = 0;
						//P1OUT ^= VERD;
					//}
					//else
					//{
						//counter++;
					//}
					
				
				/*
					Read new value from serial
					and use this value to set the
					position of the servo motor
				*/
				break;
			case DIRECTION_MSP:
				//printf("[%d]\n", adc_read(0));
				break;
			case VELOCITY_MSP:
				//printf("[%d]\n", adc_read(0));
				break;
			default:
				break;
		}
		
		
		//pwmOut(pwm0, 500);
	/*	
		if(TCount[1] <= TLimit[1]/2)
			ligled(VERM);
		else
			desled(VERM);
	*/	
		
		/*if (counter >= endcount)
		{
			counter = 0;
			P1OUT ^= VERD;
		}
		else
		{
			counter++;
		}*/
		
			
			
	}

	return 0;
}

