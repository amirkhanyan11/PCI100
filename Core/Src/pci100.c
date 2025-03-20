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

void pci100_message_handler(const char *message) {
  if (!strcmp(message, "help")) {
      cli_writeline(&huart1, "led <on/off>");
      cli_writeline(&huart1, "led blink <hz>");
      cli_writeline(&huart1, "led reset");
      cli_writeline(&huart1, "led get state");
      cli_writeline(&huart1, "dac <id> write <value>");
  }

  else if (CLI_COMMAND_NOT_FOUND == led_message_handler(message) && CLI_COMMAND_NOT_FOUND == dac_message_handler(message)) {
	  cli_writeline(&huart1, "error: command not found");
  }

}


void pci100(void) {
  blink_led(BLINK_FREQ);
  cli_engine(&huart1, pci100_message_handler);
}
