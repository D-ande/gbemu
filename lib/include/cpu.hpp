#pragma once

#include "common.hpp"
#include "instruction.hpp"
#include "bus.hpp"

struct CPURegisters
{
    uint8_t a;
    uint8_t f;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t pc; //Program Counter counting instructions
    uint16_t sp; //Stack Pointer
};

class CPU
{
    CPURegisters m_regs;
    Bus* m_bus;

    uint16_t m_fetchData;
    uint16_t m_memDest;
    uint8_t m_curOPCode;
    Inst m_curInst;

    bool m_halted;
    bool m_stepping;
    bool m_isDestMem;
    bool m_isDest16Bit;

public:
    CPU(Bus*);
    ~CPU();

    //Get instruction from addrbus op code
    void fetchInstruction();

    //Get data from registers/bus depending on addressing mode
    void fetchData();

    //cpustep will fetch instruction, process, and increment program counter
    bool cpuStep();

    void execute();

    uint16_t readReg(RegType addr);
    void setReg(RegType addr, uint16_t val);

    void proc_none();
    void proc_nop();
    void proc_ld();
};

#define CPU_FLAG_Z(cpu) BIT((CPU)m_regs.f, 7) //returns 1 or zero based on 7th bit value. Pass in cpu instance
#define CPU_FLAG_N(cpu) BIT((CPU)m_regs.f, 6) //returns 1 or zero based on 6th bit value. Pass in cpu instance
#define CPU_FLAG_H(cpu) BIT((CPU)m_regs.f, 5) //returns 1 or zero based on 5th bit value. Pass in cpu instance
#define CPU_FLAG_C(cpu) BIT((CPU)m_regs.f, 4) //returns 1 or zero based on 4th bit value. Pass in cpu instance