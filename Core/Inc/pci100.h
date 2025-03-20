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

typedef uint8_t (*message_handler_t)(const char *);

void pci100_cli(void);
void pci100_message_handler(const char *);

#endif //PCI100_H
