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
#include "../fifo/fifo.h"
#include "../adc/adc.h"
#include "../eeprom/eeprom.h"

static fifo_t UART_FIFO;

bsp_t bsp;

void bsp_run(bsp_t * const bsp) {
	bsp_blink_led(bsp);
	cli_poll(&bsp->engine);
}

uint8_t bsp_exec(bsp_t * const bsp, char *line) {
	strtrim(line, WHITESPACE);

	const uint16_t line_length = strlen(line);
	if (line_length == 0) {
		return BSP_COMMAND_NOT_FOUND;
	} else if (line_length >= FILO_BUFFER_SIZE) {
		printf("error: line too long\r\n");
		return BSP_LINE_TOO_LONG;
	}

	cmd_t cmd;
	const uint8_t status = make_cmd(&cmd, bsp, line);
	if (ESRCH == status) {
		printf("error: command not found\r\n");
		return BSP_COMMAND_NOT_FOUND;
	} else if (E2BIG == status) {
		printf("error: token too large\r\n");
		return BSP_LINE_TOO_LONG;
	}

	return cmd.exec(&cmd);
}

uint8_t bsp_init(
		bsp_t * const bsp,
		DAC_HandleTypeDef * const hdacx,
		ADC_HandleTypeDef * const hadcx,
		UART_HandleTypeDef * const huartx,
		I2C_HandleTypeDef * const hi2cx,
		I2C_HandleTypeDef * const hspix
) {
	HAL_DAC_Start(hdacx, DAC_CHANNEL_2);
	fifo_init(&UART_FIFO);
	engine_init(&bsp->engine, &UART_FIFO);

	bsp->cmds_length = 0;

	bsp->engine.bsp = bsp;

	bsp->hdacx = hdacx;
	bsp->hadcx = hadcx;
	bsp->hi2cx = hi2cx;
	bsp->huartx = huartx;
	bsp->blink_frequency = 0;
	bsp->blink_mode = BLINK_OFF;
	bsp->led_state = LED_OFF;

	bsp_cmd_add(bsp, "led",  &exec_led);
	bsp_cmd_add(bsp, "dac",  &exec_dac);
	bsp_cmd_add(bsp, "help", &exec_help);
	bsp_cmd_add(bsp, "pex",  &exec_pex);
	bsp_cmd_add(bsp, "adc",  &exec_adc);
	bsp_cmd_add(bsp, "eeprom",  &exec_eeprom);

	set_led_config(bsp);

	printf("\r\n%s", PROMPT);
	fflush(stdout);

//	HAL_UART_Receive_DMA(bsp->huartx, bsp->rx_buf, RX_BUFFER_SIZE);

	// for i2c
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

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
