#pragma once

#include "common.hpp"
#include "cart.hpp"

//Address bus is used to read ROM RAM and IO
// struct AddressBus
// {
//     uint8_t RomBank0[0x4000];
//     uint8_t RomBank1[0x4000];
//     uint8_t VRAM[0x2000];
//     uint8_t ExternalRAM[0x2000];
//     uint8_t WRAM1[0x1000];
//     uint8_t WRAM2[0x1000];
//     uint8_t EchoRAM[0x1E00]; //Reserved - Prohibited Use
//     uint8_t OAM[0xA0];
//     uint8_t Unuseable[0x60];//Reserved - Prohibited Use
//     uint8_t IOReg[0x80];
//     uint8_t HRAM[0x7F];
//     uint8_t IEReg;
// };

//Read bus takes in 16 bit address for 8 bit registers

class Bus
{
    Cart* m_Cart;
    
public:
    Bus(Cart*);
    ~Bus();

    uint8_t busRead(uint16_t);
    void busWrite(uint16_t, uint8_t);
};