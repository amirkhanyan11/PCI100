//
// Created by Artyom on 3/20/2025.
//

#ifndef PCI100_H
#define PCI100_H

#include "main.h"
#include "led.h"
#include "dac.h"
#include "cli.h"
#include "utils.h"

void pci100_cli(cli_engine_t *engine);
void pci100_message_handler(const char *);
uint8_t command_not_found_handler(const char *message);

#endif //PCI100_H
