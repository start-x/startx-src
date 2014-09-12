#include<msp430g2553.h>

#include "launchpad.h"

int main()
{
	desabWDT();
	//botao();
	dco1mhz();
	hserial();
	
	hled(VERM);
	desled(VERM);
	
	for(;;)
	{
		if (rcserial()=='R')
		{
			ligled(VERM);
			dly_coxa(3);
			wsserial("Ligado\n");
		}
		else if(rcserial()=='r')
		{
			desled(VERM);
			dly_coxa(3);
			wsserial("desligado\n");
		}
		
			
	}

	return 0;
}

