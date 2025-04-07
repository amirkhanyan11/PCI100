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
#define CLI_INVALID_OPTIONS "error: invalid options"
#define CLI_LED_INVALID_BLINK_VALUE "led: error: invalid blink frequency. Valid frequency range: [1 ... 1000]\r\n"
#define CLI_LED_ON "Led is on"
#define CLI_LED_OFF "Led is off"
#define CLI_DAC_INVALID_VALUE "dac: write: error: Invalid DAC value. Avaliable DAC value range: [ 0 ... 1 ]\r\n"
#define CLI_DAC_INVALID_OPTION "dac: write: error: Enter a decimal number\r\n"
#define CLI_DAC_INVALID_ID "dac: write: error: Invalid DAC id. Avalidable id's: [ 1 ]\r\n"

// help messages

// Led
#define CLI_LED_ON_OFF_HELP "led <on/off>                       - Turn the LED ON or OFF"
#define CLI_LED_GET_HELP	"led get                            - Get the current state of the LED"
#define CLI_LED_RESET_HELP	"led reset                          - Reset the LED mode to the one selected by MCU_CFG"
#define CLI_LED_BLINK_HELP	"led blink <hz>                     - Set the LED blink frequency (in Hz). Available frequency range: [ 1 ... 1000 ]"

#define CLI_LED_HELP CLI_LED_ON_OFF_HELP, CLI_LED_GET_HELP, CLI_LED_RESET_HELP, CLI_LED_BLINK_HELP

// Pex
#define CLI_PEX_WRITE_HELP  "pex write <addr> <val>             - Write a value to the PEX register at the specified address"
#define CLI_PEX_READ_HELP	"pex read <addr>                    - Read a value from the PEX register at the specified address"

#define CLI_PEX_HELP CLI_PEX_WRITE_HELP, CLI_PEX_READ_HELP

// DAC
#define CLI_DAC_WRITE_HELP "dac write <dac_id> <val>           - Write a value to the DAC with the specified ID. Available id's : [ 1 ]. Available floating point value range: [ 0 ... 1 ]"

#define CLI_DAC_HELP CLI_DAC_WRITE_HELP

// ADC
#define CLI_ADC_READ_HELP "adc read <adc_id>                  - Shows the digital voltage of the specified ID"

#define CLI_ADC_HELP CLI_ADC_READ_HELP

// Eeprom
#define CLI_EEPROM_WRITE_HELP 	  "eeprom write <addr> <val>          - Writes 1 byte data to eeprom's specified address"
#define CLI_EEPROM_READ_HELP  	  "eeprom read <addr>                 - Reads 1 byte data from eeprom's specified address"
#define CLI_EEPROM_READ_BULK_HELP "eeprom read_bulk <addr> <len>      - Reads specified length byte data starting from eeprom's specified address"

#define CLI_EEPROM_HELP CLI_EEPROM_WRITE_HELP, CLI_EEPROM_READ_HELP, CLI_EEPROM_READ_BULK_HELP

#endif /* SRC_CLI_CLI_STRING_LITERALS_H_ */
