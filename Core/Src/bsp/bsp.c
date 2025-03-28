/*
 * bsp.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#include "bsp.h"
#include "string.h"
#include <errno.h>
#include "../cmd/cmd.h"
#include "../led/led.h"
#include "../dac/dac.h"
#include "../led/led.h"
#include "../pex/pex.h"

void bsp_run(bsp_t * const bsp) {
	bsp_blink_led(bsp);
//	cli_process(&bsp->engine);
}

uint8_t bsp_exec(bsp_t * const bsp, char *input) {
	strtrim(input, WHITESPACE);

	if (strlen(input) == 0) {
	 return 0;
	}

	cmd_t cmd;

	if (ESRCH == make_cmd(&cmd, bsp, (char *)bsp->engine.buf)) {
	 printf("error: command not found\r\n");
	} else {
	 cmd.exec(&cmd);
	}

	return 0;
}

uint8_t bsp_init(
		bsp_t * const bsp,
		DAC_HandleTypeDef * const hdacx,
		UART_HandleTypeDef * const huartx,
		I2C_HandleTypeDef * const hi2cx
) {
	HAL_DAC_Start(hdacx, DAC_CHANNEL_1);
	engine_init(&bsp->engine, huartx);

	bsp->cmds_length = 0;

	bsp->engine.bsp = bsp;

	bsp->hdacx = hdacx;
	bsp->hi2cx = hi2cx;

	bsp->blink_frequency = 0;
	bsp->blink_mode = BLINK_OFF;
	bsp->led_state = LED_OFF;

	bsp_cmd_add(bsp, "led",  &exec_led);
	bsp_cmd_add(bsp, "dac",  &exec_dac);
	bsp_cmd_add(bsp, "help", &exec_help);
	bsp_cmd_add(bsp, "pex",  &exec_pex);

	set_led_config(bsp);

	HAL_UART_Transmit_IT(bsp->engine.huartx, (const uint8_t *)"\r\n", 2);
	HAL_UART_Transmit_IT(bsp->engine.huartx, (const uint8_t *)PROMPT, strlen(PROMPT));
	HAL_UART_Receive_IT(bsp->engine.huartx, bsp->engine.buf + bsp->engine.pos, 1);

	// for i2c
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

	return 0;
}

uint8_t bsp_cmd_add(bsp_t * const bsp, const char *name, exec_t exec) {
	if (!bsp || !name || !exec) {
		return EINVAL;
	}

	if (bsp->cmds_length == BSP_MAX_CMDS || strlen(name) > TOKEN_MAX_LENGTH) {
		return EINVAL;
	}

	strcpy(bsp->cmds[bsp->cmds_length].name, name);

	bsp->cmds[bsp->cmds_length].exec = exec;

	bsp->cmds_length += 1;

	return 0;
}


exec_t bsp_cmd_get(bsp_t * const bsp, const char *name) {
	if (!bsp || !name) {
		return NULL;
	}

	for (uint8_t i = 0; i < bsp->cmds_length; ++i) {
		if (!strcmp(bsp->cmds[i].name, name)) {
			return bsp->cmds[i].exec;
		}
	}

	return NULL;
}

void bsp_blink_led(bsp_t * const bsp) {

	if (bsp->blink_mode == BLINK_OFF) {
		return;
	}

	static uint32_t start = 0;

	const uint32_t current_tick = HAL_GetTick();

	if (current_tick >= start + bsp->blink_frequency) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
		start = HAL_GetTick();
	}
}
