#include "port.h"

// Default port
Regalia::Port::Port(uint16_t portnumber)
{
  this->portnumber = portnumber;
}

Regalia::Port::~Port()
{
}


// 8 bit port
Regalia::Port8Bit::Port8Bit(uint16_t portnumber) : Port(portnumber)
{
}

Regalia::Port8Bit::~Port8Bit()
{
}

void Regalia::Port8Bit::Write(uint8_t data)
{
  Write8(portnumber, data);
}

uint8_t Regalia::Port8Bit::Read()
{
  return Read8(portnumber);
}


// 8 bit slow port
Regalia::Port8BitSlow::Port8BitSlow(uint16_t portnumber) : Port8Bit(portnumber)
{
}

Regalia::Port8BitSlow::~Port8BitSlow()
{
}

void Regalia::Port8BitSlow::Write(uint8_t data)
{
  Write8Slow(portnumber, data);
}


// 16 bit port
Regalia::Port16Bit::Port16Bit(uint16_t portnumber) : Port(portnumber)
{
}

Regalia::Port16Bit::~Port16Bit()
{
}

void Regalia::Port16Bit::Write(uint16_t data)
{
  Write16(portnumber, data);
}

uint16_t Regalia::Port16Bit::Read()
{
  return Read16(portnumber);
}


// 32 bit port
Regalia::Port32Bit::Port32Bit(uint16_t portnumber) : Port(portnumber)
{
}

Regalia::Port32Bit::~Port32Bit()
{
}

void Regalia::Port32Bit::Write(uint32_t data)
{
  Write32(portnumber, data);
}

uint32_t Regalia::Port32Bit::Read()
{
  return Read32(portnumber);
}
