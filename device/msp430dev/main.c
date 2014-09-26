#include<msp430g2553.h>

#include <launchpad.h>
#include <Wrap.h>


int main()
{
	/* Counting parameters */
	volatile int counter = 0, endcount = 1000;
	char ch;	
	
	
	desabWDT();
	/* botao(); */
	dco1mhz();
	hserial();
	
	hled(VERM);
	desled(VERM);
	
	/* Defined in Wrap.h */
	PipeCommand cmd;

	for(;;)
	{
		cmd = getchar();
		switch(cmd)
		{
			case ALL:
				printf("[%d,%d]\n", adc_read(0),adc_read(1));
				break;
			case BREAK:
				
				ch = getchar();
				
				if (counter >= endcount)
				{
					counter = 0;
					alterled(unsigned volatile numled);
				}
				else
				{
					counter++;
				}
				
				if((ch >= 48) && (ch <= 58))
					endcount = 1000 + (int) ((unsigned char) ch-48)*50000/10;
				//wcserial(ch);
		
				
				
				
				
				/*
					Read new value from serial
					and use this value to set the
					position of the servo motor
				*/
				break;
			case DIRECTION:
				printf("[%d]\n", adc_read(0));
				break;
			default:
				break;
		}		
			
	}

	return 0;
}

