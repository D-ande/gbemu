#include "bus.hpp"

Bus::Bus(Cart* cart)
{
    m_Cart = cart;
}

Bus::~Bus()
{
}

uint8_t Bus::busRead(uint16_t addr)
{
    uint8_t val = 0;
    if(addr < 0x8000)
    {
        val = m_Cart->cartRead(addr);
    }
    else
    {
        throw std::out_of_range("Accessing memory out of range");
    }
    return val;
}

void Bus::busWrite(uint16_t addr, uint8_t val)
{
    NOT_IMPL
}