#include "adc.h"
#include "typedefs.h"
#include <errno.h>
#include <string.h>
#include "utils.h"
#include "cli_string_literals.h"

#define COUNTER 10
#define ADC_SUPPORTED_CHANNELS_SIZE 1
static uint32_t adc_channels[ADC_SUPPORTED_CHANNELS_SIZE] = {ADC_CHANNEL_10};

static bool adc_supported_channel(uint8_t channel_id)
{
	return (channel_id > 0 && channel_id <= ADC_SUPPORTED_CHANNELS_SIZE);
}

static void adc_error_handle(void)
{
	printf("  Something went wrong in channel select process.\r\n");
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

static uint8_t __adc_err(void)
{
	printf("adc: read: %s\r\n", CLI_INVALID_OPTIONS);
	printchunk("Usage:", CLI_ADC_HELP, NULL);
	return EINVAL;
}

static uint8_t adc_read(cmd_t * const cmd)
{

	if (cmd->argc != 2) {
		return __adc_err();
	}
	uint32_optional_t channel = satoi(cmd->argv[1]);

	if (!channel.has_val || !adc_supported_channel(channel.val)) {
		return __adc_err();
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
	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("Usage:", CLI_ADC_HELP, NULL);
	} else if (!strcmp(option, "read")) {
		status = adc_read(cmd);
	} else {
		printf("adc: error: invalid option `%s`. See adc -h\r\n", option);
		status = BSP_INVALID_OPTIONS;
	}

	return status;
}
