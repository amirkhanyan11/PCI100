/*
 * help.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */


#include "bsp.h"
#include <errno.h>

uint8_t exec_help(cmd_t * const cmd) {
	if (cmd->argc != 0) {
		printf("help: error: invalid options\r\n");
		return EINVAL;
	}
	printf("\r\nAvailable commands:\r\n"
		   "\r\n  pex write <addr> <val>   - Write a value to the PEX register at the specified address"
		   "\r\n  pex read <addr>          - Read a value from the PEX register at the specified address"
		   "\r\n  led <on/off>             - Turn the LED ON or OFF"
		   "\r\n  led get                  - Get the current state of the LED"
		   "\r\n  led reset                - Reset the LED mode to the one selected by MCU_CFG"
		   "\r\n  led blink <hz>           - Set the LED blink frequency (in Hz). Available frequency range: [ 1 ... 1000 ]"
		   "\r\n			    Available frequency range: [ 1 ... 1000 ] \r\n"
		   "  dac write <dac_id> <val> - Write a value to the DAC with the specified ID."
		   "\r\n			    Available id's : [ 1 ]. Available floating point value range: [ 0 ... 1 ]\r\n\r\n"
	);


	return 0;
}
