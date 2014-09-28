#include "adc.h"

/**
 * 	@fn adc_read
 * 	@brief Read a Analogic port 
 *	@param unsigned char CH : Input the port to read
 *	@return Return the value in Long Int.
*/
int adc_read(unsigned int ch){	
	
	volatile int delay;
	
	#ifdef __MSP430F2274__
		switch(ch){
			case 0:
				ADC10CTL1 = INCH_0;
				break;
			case 1:	
				ADC10CTL1 = INCH_1;
				break;
			case 2:
				ADC10CTL1 = INCH_2;
				break;
			case 3:
				if((ADC10CTL0 & SREF_6))
					return -EPERM;  /* Operation not permitted */      
				ADC10CTL1 = INCH_3;
				break;
			case 4:
				if((ADC10CTL0 & SREF_6))
					return -EPERM; /* Operation not permitted */         
				ADC10CTL1 = INCH_4;
				break;
			case 12:
				ADC10CTL1 = INCH_12;
				break;
			case 13:
				ADC10CTL1 = INCH_13;
				break;
			case 14:
				ADC10CTL1 = INCH_14;
				break;
			case 15:
				ADC10CTL1 = INCH_15;
				break;
			default:
				return -EPERM; //Operation not permitted 
		}
	
	#elif defined(__MSP430G2553__)
		switch(ch){
			case 0:
				ADC10CTL1 = INCH_0;
				break;
			case 1:	
				ADC10CTL1 = INCH_1;
				break;
			case 2:
				ADC10CTL1 = INCH_2;
				break;
			case 3:
				if((ADC10CTL0 & SREF_6))
					return -EPERM;  /* Operation not permitted */      
				ADC10CTL1 = INCH_3;
				break;
			case 4:
				if((ADC10CTL0 & SREF_6))
					return -EPERM; /* Operation not permitted */         
				ADC10CTL1 = INCH_4;
				break;
			case 5:
				ADC10CTL1 = INCH_5;
				break;
			case 6:
				ADC10CTL1 = INCH_6;
				break;
			case 7:  
				ADC10CTL1 = INCH_7;
				break;
			default:
				return -EPERM; /* Operation not permitted */
		}
	#else
		#error "No such device!"
		return -ENXIO;
	#endif
	
	if(!( ADC10CTL0 && ADC10ON))
		adc_eref_off() ;                

	for(delay=35;delay==0;delay--);

	ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	__bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
	ADC10CTL0 |= ~ENC;

	return ADC10MEM;
}

/**
 * @fn adc_eref_off
 * @brief It will hold the configuration of the ADC, and change it according to the OP variable.
 * @param n/a
 * @return Returns a code with the new configuration		
*/
int adc_eref_off() 
{
	#if defined(__MSP430G2553__) || defined(__MSP430F2274__)
	
		ADC10AE0 = 0xff;  					/* Seleção das portas como OUTPUT  */
	
		ADC10CTL0 |= ~ENC;
	
		ADC10CTL0 = 
		ADC10ON + 
		SREF_0+				/* Referencia VCC */
		ADC10SHT_3 + 
		ADC10IE; 
		return (ADC10CTL0 - (ADC10ON + SREF_0 + ADC10SHT_3 + ADC10IE));
	#else
		#error "No such device!"
		return -ENXIO; /* No such device */
	#endif
	
	
	return -ENXIO; /* No such device */
	}


/**
 * @fn adc_eref_on
 * @brief Reconfigure the parameters of the ADC to enable Veref+ and Veref-
 * @param n/a
 * @return Returns the new configuration		
*/
int adc_eref_on() 
{
	#if defined(__MSP430F2274__) || defined(__MSP430G2553__)
		
/*		if( ADC10CTL0 && ADC10ON)
			return -EPERM; /* Operation not permitted */
 			
		// Modo com referencia externa nos pinos 6 (-) e 7 (+)
			
		volatile int delay;
		ADC10AE0 |= 0x3ff;		/* seleção de todas as portas exceto as que correspondem a eref+/-  */
		
		ADC10CTL0 |= ~ENC;
		ADC10CTL0 |= 
		ADC10ON + 
		SREF_6+				/* Referencia VCC */
		ADC10SHT_3 + 
		ADC10IE; 
		
		for(delay=35;delay==0;delay--);
		return SUCCESS;
		
	
	#else
		#error "No such device!"
	#endif
	return -ENXIO;
}

/**
 * @fn adc_close
 * @brief It will stop ADC, free the ports, and reset the OP configuration. 
 * @param unsigned char CH : Input the port to read
 * @return Return the value in Long Int.
	*/
void adc_close()
{
	#if defined(__MSP430G2553__) || defined(__MSP430F2274__)
		
	ADC10CTL1 |= ~ADC10ON;
		
	#endif
	
} 

// *************************************************************************************************
// @fn          ADC12ISR
// @brief       Store ADC12 conversion result. Set flag to indicate data ready.
// @param       none
// @return      none
// *************************************************************************************************
//Rotina de interrupção
#if defined(__MSP430G2553__) || defined(__MSP430F2274__)

	/* pfs wrapped the following to accommodate mspgcc compiler */
	#ifdef __GNUC__
	#include <legacymsp430.h>
	interrupt (ADC10_VECTOR) ADC10ISR (void)
	#else
	#pragma vector=ADC10_VECTOR
	__interrupt void ADC10ISR (void)
	#endif
{
	__bic_SR_register_on_exit(LPM0_bits + GIE);
}
#else
	#error "No such device!"
		
#endif

