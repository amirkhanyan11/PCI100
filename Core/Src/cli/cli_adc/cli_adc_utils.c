/*
 * cli_adc_utils.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "cli_adc.h"
#include "adc.h"
#include "cli.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

uint8_t __adc_err(void)
{
	printf("adc: read: %s\r\n", CLI_INVALID_OPTIONS);
	printchunk("Usage:", CLI_ADC_HELP, NULL);
	return EINVAL;
}

bool adc_supported_channel(uint8_t channel_id)
{
	return (channel_id > 0 && channel_id <= adc_get_channels_size());
}
