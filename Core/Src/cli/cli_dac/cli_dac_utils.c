/*
 * cli_dac_utils.c
 *
 *  Created on: Apr 11, 2025
 *      Author: Tigran
 */

#include "cli_dac.h"
#include "dac.h"

bool dac_supported_channel(uint8_t channel_id)
{
	return (channel_id > 0 && channel_id <= dac_get_channels_size());
}
