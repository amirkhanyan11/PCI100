#include "eeprom.h"
#include <errno.h>
#include <string.h>
#include "../utils/utils.h"
#include "../cli/cli_string_literals.h"

static void chip_select(bool mod)
{
	if (mod) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	}
	HAL_Delay(1);
}

static void write_handler(bool mod, SPI_HandleTypeDef *hspi1)
{
	uint8_t wr_mod = mod ? SPI_WREN : SPI_WRDI;

    chip_select(true);
    HAL_SPI_Transmit(hspi1, &wr_mod, 1, 100);
    chip_select(false);
}

static uint8_t __eeprom_helper(const char * const cmd, const char * const s)
{
	printf("eeprom: %s: %s", cmd, CLI_INVALID_OPTIONS);
	printf("%s", s);
	return EINVAL;
}

// Eeprom_write - writes a byte of data in received address
// address - where to write
// data - what to write
static uint8_t eeprom_write(cmd_t * const cmd)
{

	if (cmd->argc != 3) {
		return __eeprom_helper(cmd->argv[0], HELP_CLI_EEPROM_WRITE);
	}
	uint32_optional_t val_o = satoi(cmd->argv[1]);

	if (!val_o.has_val) {
		return __eeprom_helper(cmd->argv[0], HELP_CLI_EEPROM_WRITE);
	}

	uint16_t address = val_o.val;

	val_o = satoi(cmd->argv[2]);

	if (!val_o.has_val) {
		return __eeprom_helper(cmd->argv[0], HELP_CLI_EEPROM_READ_BULK);
	}

    uint8_t data = val_o.val;

    uint8_t arr[SPI_SIZE] = {SPI_WRITE, address >> 8, address, data};

    write_handler(true, cmd->bsp->hspix);
    chip_select(true);

    if ( HAL_SPI_Transmit(cmd->bsp->hspix, arr, SPI_SIZE, 1000) == HAL_OK) {
        printf("Message successfully transmitted.\r\n");
    } else {
    	printf("Error occurred during write process.\r\n");
    }
    chip_select(false);
    write_handler(true, cmd->bsp->hspix);
    return HAL_OK;
}

// Eeprom_read - reads a byte of data from received address and shows it
// address - where from to read
static uint8_t eeprom_read(cmd_t * const cmd)
{
	if (cmd->argc != 2) {
		return __eeprom_helper(cmd->argv[0], HELP_CLI_EEPROM_READ);
	}
	uint32_optional_t val_o = satoi(cmd->argv[1]);

	if (!val_o.has_val) {
		return __eeprom_helper(cmd->argv[0], HELP_CLI_EEPROM_READ);
	}

	uint16_t address = val_o.val;
    uint8_t data[SPI_SIZE] = {0};
    uint8_t arr[SPI_SIZE] = {SPI_READ, address >> 8, address, 0};

    chip_select(true);

    if (HAL_SPI_TransmitReceive(cmd->bsp->hspix, arr, data, SPI_SIZE, 1000) == HAL_OK) {
   		printf("%d\r\n", data[SPI_SIZE - 1]);
    } else {
    	printf("Error occurred during read process.\r\n");
    }
    chip_select(false);
    return HAL_OK;
}

// Eeprom_read_bulk - reads a data of received size from received address and shows them
// address - where from to start read process
// size - counts of byte to read
static uint8_t eeprom_read_bulk(cmd_t * const cmd)
{

	if (cmd->argc != 3) {
		return __eeprom_helper(cmd->argv[0], HELP_CLI_EEPROM_READ_BULK);
	}
	uint32_optional_t val_o = satoi(cmd->argv[1]);

	if (!val_o.has_val) {
		return __eeprom_helper(cmd->argv[0], HELP_CLI_EEPROM_READ_BULK);
	}

	uint16_t address = val_o.val;

	val_o = satoi(cmd->argv[2]);

	if (!val_o.has_val) {
		return __eeprom_helper(cmd->argv[0], HELP_CLI_EEPROM_READ_BULK);
	}

    uint16_t size = val_o.val;

    uint8_t transmit[SPI_SIZE] = {SPI_READ, address >> 8, address, 0};
    uint8_t receive[SPI_SIZE + size];

    memset(receive, 0, SPI_SIZE + size);

    chip_select(true);
    if (size != 0 && HAL_SPI_TransmitReceive(cmd->bsp->hspix, transmit, receive, SPI_SIZE + size, 1000) == HAL_OK) {
        for (uint8_t i = SPI_SIZE - 1; i < SPI_SIZE + size - 1; ++i) {
        	printf(((i != SPI_SIZE + size - 2) ? "%d, " : "%d\r\n"), receive[i]);
        }
    } else {
    	printf("Error occurred during read process.\r\n");
    }
    chip_select(false);
    return HAL_OK;
}

uint8_t exec_eeprom(cmd_t * const cmd)
{
	const char * const option = cmd->argv[0];

	if (!strcmp(option, "write")) {
		return eeprom_write(cmd);
	} else if (!strcmp(option, "read")) {
		return eeprom_read(cmd);
	} else if (!strcmp(option, "read_bulk")) {
		return eeprom_read_bulk(cmd);
	}

	printf(CLI_COMMAND_NOT_FOUND);
	printf(HELP_CLI_EEPROM_WRITE);
	printf(HELP_CLI_EEPROM_READ);
	printf(HELP_CLI_EEPROM_READ_BULK);

	return 127;
}
