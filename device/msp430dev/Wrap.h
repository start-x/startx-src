#ifndef __MSP430G2553__
	#include <signal.h>
#endif

/**
 * Macros used with Python
 */
#define SIG1 30 /*SIGUSR1 */
#define SIG2 31 /*SIGUSR2 */
#define SIG3 14 /*SIGALRM */
#define ACTIVE_FILE "/tmp/bikex_active"
#define PASSIVE_FILE "/tmp/bikex_passive"

/**
 * Macros to define the output
 * from sensor
 */

#define ALL_VALUES 0
#define DIRECTION_MSP 1
#define VELOCITY_MSP 2
#define BREAK_MSP 3