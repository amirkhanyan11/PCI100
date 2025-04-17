/*
 * pex.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#include "pex.h"

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;
extern I2C_HandleTypeDef hi2c3;

static I2C_HandleTypeDef * i2c[] = {&hi2c1, &hi2c2, &hi2c3};

uint8_t pex_write(uint8_t hi2cx, const uint32_t register_addr, const uint32_t val) {

	// the remaining 4 bytes of the payload are initialized with val
	uint8_t payload[8] = { PEX_CB1_WRITE_REGISTER, PEX_CB2_TRANSPARENT_PORTS, PEX_CB3_ENABLE_ALL, register_addr };

	for (uint8_t i = 4, shift_offset = 24; i < 8; ++i, shift_offset -= 8) {
		payload[i] = (val >> shift_offset);
	}

	return HAL_I2C_Master_Transmit(i2c[hi2cx], DRIVER_PEX_SLAVE_ADDRESS, payload, sizeof(payload), HAL_MAX_DELAY);
}

uint32_t pex_read(uint8_t hi2cx, const uint32_t register_addr) {

	uint8_t payload[] = { PEX_CB1_READ_REGISTER, PEX_CB2_TRANSPARENT_PORTS, PEX_CB3_ENABLE_ALL, register_addr };

	if (HAL_OK != HAL_I2C_Master_Transmit(i2c[hi2cx], DRIVER_PEX_SLAVE_ADDRESS, payload, sizeof(payload), 1000)) {
		return -1;
	}

	uint8_t RX_Buf[4] = {0};

	if (HAL_OK != HAL_I2C_Master_Receive(i2c[hi2cx], DRIVER_PEX_SLAVE_ADDRESS, RX_Buf, sizeof(RX_Buf), 1000)) {
		return -1;
	}

	uint32_t res = 0;

	for (uint8_t i = 0; i < 4; ++i) {
		res = (res << 8) | RX_Buf[i];
	}

	return res;
}
