/*
 * cli_string_literals.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef SRC_CLI_CLI_STRING_LITERALS_H_
#define SRC_CLI_CLI_STRING_LITERALS_H_

// error messages
#define CLI_COMMAND_NOT_FOUND "error: command not found\r\n"
#define CLI_INVALID_OPTIONS "error: invalid options\r\n"
#define CLI_LED_INVALID_BLINK_VALUE "led: error: invalid blink frequency. Valid frequency range: [1 ... 1000]\r\n"
#define CLI_LED_ON "Led is on"
#define CLI_LED_OFF "Led is off"
#define CLI_DAC_INVALID_VALUE "dac: write: error: Invalid DAC value. Avaliable DAC value range: [ 0 ... 1 ]\r\n"
#define CLI_DAC_INVALID_OPTION "dac: write: error: Enter a decimal number\r\n"
#define CLI_DAC_INVALID_ID "dac: write: error: Invalid DAC id. Avalidable id's: [ 1 ]\r\n"
#define HELP_CLI_ADC "adc read <adc_id>\t\tShows the digital voltage of the specified ID\r\n"

// help messages
#define CLI_LED_HELP "\r\n  led <on/off>             - Turn the LED ON or OFF" \
				     "\r\n  led get                  - Get the current state of the LED" \
		   	   	   	 "\r\n  led reset                - Reset the LED mode to the one selected by MCU_CFG" \
					 "\r\n  led blink <hz>           - Set the LED blink frequency (in Hz). Available frequency range: [ 1 ... 1000 ]" \
		   	   	     "\r\n			    Available frequency range: [ 1 ... 1000 ] \r\n"

#define CLI_PEX_HELP "\r\n  pex write <addr> <val>   - Write a value to the PEX register at the specified address" \
		   	   	   	 "\r\n  pex read <addr>          - Read a value from the PEX register at the specified address"

#define CLI_DAC_HELP "  dac write <dac_id> <val> - Write a value to the DAC with the specified ID." \
		   	   	   	 "\r\n			    Available id's : [ 1 ]. Available floating point value range: [ 0 ... 1 ]\r\n\r\n"

#endif /* SRC_CLI_CLI_STRING_LITERALS_H_ */
