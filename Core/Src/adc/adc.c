#include "adc.h"
#include "typedefs.h"
#include <errno.h>
#include <string.h>
#include "../utils/utils.h"
#include "../cli/cli_string_literals.h"

#define COUNTER 10
#define ADC_SUPPORTED_CHANNELS_SIZE 1
static uint32_t adc_channels[ADC_SUPPORTED_CHANNELS_SIZE] = {ADC_CHANNEL_10};

static void adc_supported_ids(uint8_t max_id)
{
	printf("Supported channel's IDs are:\r\n");
	for (uint8_t i = 1; i <= max_id; ++i){
			printf(((i == max_id) ? "%d\r\n" : "%d, "), i);
	}
}

static bool adc_supported_channel(uint8_t channel_id)
{
	return (channel_id > 0 && channel_id <= ADC_SUPPORTED_CHANNELS_SIZE);
}

static void adc_error_handle(void)
{
	printf("Something went wrong in channel select process.\r\n");
	__disable_irq();
	while (1)
	{
	}
}

static void adc_channels_handler(ADC_HandleTypeDef *hadc1, uint8_t channel_id)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = adc_channels[channel_id - 1];
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(hadc1, &sConfig) != HAL_OK)
	{
		adc_error_handle();
	}
}

static uint8_t __adc_helper(void)
{
	printf("adc: read: %s", CLI_INVALID_OPTIONS);
	printf("%s", HELP_CLI_ADC);
	adc_supported_ids(ADC_SUPPORTED_CHANNELS_SIZE);
	return EINVAL;
}

static uint8_t adc_read(cmd_t * const cmd)
{

	if (cmd->argc != 2) {
		return __adc_helper();
	}
	uint32_optional_t channel = satoi(cmd->argv[1]);

	if (!channel.has_val || !adc_supported_channel(channel.val)) {
		return __adc_helper();
	}
	adc_channels_handler(cmd->bsp->hadcx, channel.val);
	HAL_ADC_Start(cmd->bsp->hadcx);
	float res = 0;
	uint16_t i = 0;
	while (i++ < COUNTER) {
		HAL_ADC_PollForConversion(cmd->bsp->hadcx, 10);
		res += HAL_ADC_GetValue(cmd->bsp->hadcx);
	}
	res /= COUNTER;
	res *= VOLTAGE_MAX / BIT_RANGE_12;

	printf("%.2fV\r\n", res);
	return (HAL_ADC_Stop(cmd->bsp->hadcx));
}

// ADC_Handler - handles received analog, convert to digital and shows voltage
uint8_t exec_adc(cmd_t * const cmd)
{
	const char * const option = cmd->argv[0];

	if (!strcmp(option, "read")) {
		return adc_read(cmd);
	}

	printf("adc: %s", CLI_INVALID_OPTIONS);
	return BSP_INVALID_OPTIONS;
}
