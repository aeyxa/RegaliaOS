#ifndef __PORT_H
#define __PORT_H

#include "common.h"

uint8_t inportb (unsigned short port);
void outportb (uint16_t port, uint8_t data);

#endif
