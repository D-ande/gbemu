#pragma once

#include <mutex>

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

    static GbEmu* instance;
    static std::mutex mutex_;

    GbEmu(std::string);
    GbEmu(const GbEmu&) = delete;
    GbEmu& operator=(const GbEmu&) = delete;

    int emuMain();

public:

    static GbEmu* getInstance(std::string fileName = "") {
        if (instance == nullptr)
        {
            instance = new GbEmu(fileName);
        }
        return instance;
    }

    ~GbEmu();

    void printTicks();
    void cycle(int);

    friend int main(int argc, char** argv);
};