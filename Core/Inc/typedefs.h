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
typedef uint8_t (*handle_key)(cli_engine_t *const);

// cmd.h
typedef struct cmd_s cmd_t;
typedef uint8_t (*exec_t) (cmd_t * const);

// bsp.h
typedef struct bsp_s bsp_t;
typedef struct bsp_cmd_s bsp_cmd_t;

#endif /* INC_TYPEDEFS_H_ */
