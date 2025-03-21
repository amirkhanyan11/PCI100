//
// Created by Artyom on 3/20/2025.
//

#ifndef PCI100_H
#define PCI100_H

#include "main.h"
#include "../led/led.h"
#include "../dac/dac.h"
#include "../cli/cli.h"
#include "../utils/utils.h"

#define BSP_COMMANDS_MAX 1024

// error codes
#define BSP_OK 0
#define BSP_ERROR 1

typedef struct
{
	cmd_handler_t arr[BSP_COMMANDS_MAX];
	uint32_t length;
} bsp_cmdmap_t;


void bsp_config();
void bsp_run(cli_engine_t *engine);
void bsp_message_handler(const char *);
uint8_t bsp_cmd_push(cmd_handler_t c);
uint8_t bsp_cmd_pop();
uint8_t command_not_found_handler(const char *message);

#endif //PCI100_H
