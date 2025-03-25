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
	printf("\r\n");
	printf("Available commands:\r\n\n");
	printf("  led <on/off>             - Turn the LED on or off\r\n\n");
	printf("  led reset                - Reset the LED mode to the one selected by MCU_CFG\r\n\n");
	printf("  led get                  - Get the current state of the LED\r\n\n");
	printf("  pex write <addr> <val>   - Write a value to the PEX register at the specified address\r\n\n");
	printf("  pex read <addr>          - Read a value from the PEX register at the specified address\r\n\n");
	printf("  dac write <dac_id> <val> - Write a value to the DAC with the specified ID\r\n\n");
	printf("  led blink <hz>           - Set the LED blink frequency (in Hz). Available blink frequencies: [ 1Hz, 2Hz, 10Hz, 20Hz, 50Hz, 100Hz, 1000Hz ] \r\n\n");
	printf("\r\n");


	return 0;
}
