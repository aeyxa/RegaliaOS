#pragma once

#include <Common/common.h>

uint8_t inportb (unsigned short port);
void outportb (uint16_t port, uint8_t data);
