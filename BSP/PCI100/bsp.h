/*
 * bsp.h
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "main.h"
#include "typedefs.h"

struct pci100_bsp_s
{
	const uint8_t huartx;
	const uint8_t hdacx;
	const uint8_t hi2cx;
	const uint8_t hadcx;
	const uint8_t hspix;
};

void			bsp_init(void);
pci100_bsp_t	*bsp_get(void);


#endif /* SRC_BSP_BSP_H_ */

