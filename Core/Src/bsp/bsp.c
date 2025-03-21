//
// Created by Artyom on 3/20/2025.
//

#include "bsp.h"

#include <string.h>

extern DAC_HandleTypeDef hdac;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

extern volatile uint32_t BLINK_FREQ;
extern volatile uint32_t LED_MODE;


bsp_cmdmap_t CMDS = {0};


message_handler_t bsp_cmd_find(const char *name) {

	for (uint8_t i = 0; i < CMDS.length; ++i) {
		if (!strcmp(CMDS.arr[i].name, name)) {
			  return CMDS.arr[i].handle;
		  }
	  }
	return NULL;
}

uint8_t bsp_cmd_push(cmd_handler_t c) {
	if (CMDS.length == BSP_COMMANDS_MAX) {
		return BSP_ERROR;
	}

	CMDS.arr[CMDS.length] = c;

	CMDS.length++;

	return BSP_OK;
}


uint8_t bsp_cmd_pop() {
	if (CMDS.length == 0) {
		return BSP_ERROR;
	}

	memset((CMDS.arr + CMDS.length - 1), 0, sizeof(cmd_handler_t));

	CMDS.length--;

	return BSP_OK;
}


void bsp_message_handler(const char *message) {

	char message_copy[CLI_BUFFER_SIZE] = {0};

	strcpy(message_copy, message);

	if (!strcmp(message_copy, "help")) {
		  cli_writeline(&huart1, "led <on/off>");
		  cli_writeline(&huart1, "led blink <hz>");
		  cli_writeline(&huart1, "led reset");
		  cli_writeline(&huart1, "led get state");
		  cli_writeline(&huart1, "dac <id> write <value>");
	  }

	  const char *cmd_name = strtok(message_copy, CLI_WHITESPACE_DELIMITERS);

	  if (!cmd_name) {
		  return;
	  }

	  message_handler_t handle = bsp_cmd_find(cmd_name);

//	  handle()

	  cli_writeline(&huart1, "error: command not found");
}

// call this function before using any bsp cli functionality
void bsp_config() {
	cmd_handler_t led = {
			.name = "led",
			.handle = led_message_handler
	};
	cmd_handler_t dac = {
			.name = "dac",
			.handle = dac_message_handler
	};
	bsp_cmd_push(led);
	bsp_cmd_push(dac);
}

void bsp_run(cli_engine_t *engine) {
	blink_led(BLINK_FREQ);
	cli_process(engine);
}


uint8_t command_not_found_handler(const char *message) {
	cli_writeline(&huart1, "error: command not found");
	return CLI_COMMAND_NOT_FOUND;
}



