/*
 * typedefs.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef INC_TYPEDEFS_H_
#define INC_TYPEDEFS_H_

#include <stdint.h>

// cli.h
typedef struct cli_engine_s cli_engine_t;

// cmd.h
typedef struct cmd_s cmd_t;
typedef uint8_t (*exec_t) (cmd_t * const);

// app.h
typedef struct app_s app_t;
typedef struct cmd_config_s cmd_config_t;

// bsp.h
typedef struct bsp_s bsp_t;

// fifo.h
typedef struct fifo_s fifo_t;

// filo.h
typedef struct filo_s filo_t;

// history.h
typedef struct history_s history_t;

// utils.h
typedef struct uint32_optional_s uint32_optional_t;
typedef struct double_optional_s double_optional_t;

// led.h
typedef struct led_s led_t;

// chain.h
typedef struct chain_s chain_t;
typedef uint8_t (*chain_fn_t)();

#endif /* INC_TYPEDEFS_H_ */
