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
	ligled(VERM);
	//P1OUT ^= VERM;
	/* Defined in Wrap.h */
	int cmd;

	for(;;)
	{
		//P1OUT ^= VERM;
		cmd = getchar();
		switch(cmd)
		{
			case ALL_VALUES:
				//printf("[%d,%d]\n", adc_read(0),adc_read(1));
				break;
			case 'a':
			case BREAK_MSP:
			
				//dly_coxa(1000);
				
				ch = getchar();
								
				if((ch >= '0') && (ch <= '9'))
					endcount = 1000 + (int) ((unsigned char) ch-'0')*10000/10;
					
					//if(counter >= endcount)
					//{
						counter = 0;
						P1OUT ^= VERD;
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
		
		
		if (counter >= endcount)
		{
			counter = 0;
			P1OUT ^= VERM;
		}
		else
		{
			counter++;
		}		
			
	}

	return 0;
}

