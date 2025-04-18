/*
 * app.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#include <errno.h>
#include "app.h"
#include "string.h"
#include "fifo.h"
#include "cmd.h"
#include "utils.h"
#include "cli_string_literals.h"
#include "cmsis_os.h"

#include "bsp.h"

extern fifo_t UART_FIFO1;

static app_t *g_app;

void start_led_blink_task(void const * argument);
void start_cli_task(void const * argument);
osThreadId led_blink_task_hadnle;
osThreadId cli_task_hadnle;

void app_run(app_t * const app) {


	/* Create the thread(s) */
	/* definition and creation of defaultTask */
#if 1 //TODO: Integrate FreeRTOS
	osThreadDef(led_task, start_led_blink_task, osPriorityNormal, 0, 1280);
	led_blink_task_hadnle = osThreadCreate(osThread(led_task), NULL);

	osThreadDef(cli_task, start_cli_task, osPriorityRealtime, 0, 1280);
	cli_task_hadnle = osThreadCreate(osThread(cli_task), NULL);

	/* Start scheduler */
	osKernelStart();

#else
	/* We should never get here as control is now taken by the scheduler */
	led_blink(&app->led);
	cli_poll(&app->engine);

#endif

}

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void start_led_blink_task(void const * argument)
{
	for(;;)
	{
		led_blink(&g_app->led);

	}
}

void start_cli_task(void const * argument)
{
	for(;;)
	{
		cli_poll(&g_app->engine);

	}
}



uint8_t app_router(app_t * const app, char *line) {
	strtrim(line, WHITESPACE);

	const uint16_t line_length = strlen(line);
	if (line_length == 0) {
		return APP_COMMAND_NOT_FOUND;
	} else if (line_length >= FILO_BUFFER_SIZE) {
		printf("error: line too long\r\n");
		return APP_LINE_TOO_LONG;
	}

	cmd_t cmd;
	const uint8_t status = make_cmd(&cmd, app, line);
	if (ESRCH == status) {
		printf("error: command not found\r\n");
		return APP_COMMAND_NOT_FOUND;
	} else if (E2BIG == status) {
		printf("error: token too large\r\n");
		return APP_LINE_TOO_LONG;
	}

	return cmd.exec(&cmd);
}

uint8_t app_init(app_t * const app) {
	g_app = app;
	app->sc_arr.length = 0;

	app->bsp = bsp_get();

	engine_init(&app->engine, app, &UART_FIFO1, app->bsp->huartx);

	fifo_init(&UART_FIFO1);

	led_init(&app->led);

	cli_config(app);

	printf("\r\n%s", PROMPT);
	fflush(stdout);

	return 0;
}
