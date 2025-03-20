//
// Created by Artyom on 3/20/2025.
//

#include "pci100.h"
#include <string.h>

extern DAC_HandleTypeDef hdac;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

extern volatile uint32_t BLINK_FREQ;
extern volatile uint32_t LED_MODE;

static uint8_t (*HANDLERS[])(const char *) = {
		led_message_handler,
		dac_message_handler,
		command_not_found_handler,
		NULL
};


void pci100_message_handler(const char *message) {
  if (!strcmp(message, "help")) {
      cli_writeline(&huart1, "led <on/off>");
      cli_writeline(&huart1, "led blink <hz>");
      cli_writeline(&huart1, "led reset");
      cli_writeline(&huart1, "led get state");
      cli_writeline(&huart1, "dac <id> write <value>");
  }

  for (uint16_t i = 0; HANDLERS[i]; ++i) {
	  if (CLI_COMMAND_NOT_FOUND != HANDLERS[i](message)) {
		  break;
	  }
  }
}


void pci100_cli(void) {
	blink_led(BLINK_FREQ);
	cli_engine(&huart1, pci100_message_handler);
}


uint8_t command_not_found_handler(const char *message) {
	cli_writeline(&huart1, "error: command not found");
	return CLI_COMMAND_NOT_FOUND;
}
