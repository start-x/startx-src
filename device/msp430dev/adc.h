#include <legacymsp430.h>
#include <msp430.h>

#define SUCCESS		0
//! Operation not permitted 
#define	EPERM		 1	
//! No such device or address 
#define	ENXIO		 6	
/**
 * 	@fn adc_read
 * 	@brief Read a Analogic port 
 *	@param unsigned char CH : Input the port to read
 *	@return Return the value in Long Int.
*/
extern
int adc_read(unsigned int ch);

/**
 * @fn adc_eref_on
 * @brief Reconfigure the parameters of the ADC to enable Veref+ and Veref-
 * @param n/a
 * @return Returns the new configuration		
*/
int adc_eref_on(); 

/**
 * @fn adc_eref_off
 * @brief It will hold the configuration of the ADC, and change it according to the OP variable.
 * @param n/a
 * @return Returns a code with the new configuration		
*/
int adc_eref_off();

/**
 * @fn adc_close
 * @brief It will stop ADC, free the ports, and reset the OP configuration. 
 * @param unsigned char CH : Input the port to read
 * @return Return the value in Long Int.
	*/
void adc_close();
