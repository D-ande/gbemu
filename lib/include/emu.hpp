#pragma once

#include "common.hpp"
#include "cpu.hpp"
#include "cart.hpp"
#include "bus.hpp"

class GbEmu
{
    Cart* m_Cart;
    Bus* m_Bus;
    CPU* m_CPU;

    std::string m_fileName;
    bool m_running = false;
    int m_ticks = 0;
    int m_paused = false;

public:
    GbEmu(std::string);
    ~GbEmu();

    void printTicks();
    int emuMain();
};