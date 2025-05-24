#include "cpu.hpp"

CPU::CPU(Bus* bus)
{
    m_bus = bus;
    m_regs.pc = 0x100;
    m_regs.a = 0x01;
}

CPU::~CPU()
{

}

void CPU::fetchInstruction()
{
    //Read addr bus and get the current program counter address opcode

    m_curOPCode = m_bus->busRead(m_regs.pc++); // Read instruction will always increment forward 1. 
                                               // Depending on instruction we may have to increment more during decode.
                                               // This will pass pc first and then increment afterwards.
    if (m_curOPCode == 0xC3) //Delete this if later when implemented
    {
        m_curInst = Inst(IN_JP, AM_D16);
    }
    else if (m_curOPCode > 0x08){
        std::cout << "Bad OP code: " << m_curOPCode << std::endl;
        throw std::out_of_range("OP Code not implemented");
    }
    else{
        m_curInst = instructionSet[m_curOPCode];
    }
}

void CPU::fetchData()
{
    // Check what registers we're interacting with
    m_memDest = 0;
    bool isDestMem = false;
    int inc = 0;
    // Check pc increment (if 16 bit increment pc twice)
    //if(m_curInst == NULL) { return; } //Need to get data based on what address mode (first is dest, second is source) 
                                        //data we're fetching is the value at source register (second item in AddrMode)
    switch(m_curInst.mode){
        case AM_IMP: break;

        case AM_R:
        //Get R
            m_fetchData = readReg(m_curInst.reg1); //reg1 & reg2 is memory address of what register we want to read.
            inc = 1; // increment 1 because reading 8 bit reg
            break;
        
        case AM_R_D8: //D8 as source tells us to grab the next byte from bus because instruction is longer
            m_fetchData = m_bus->busRead(m_regs.pc);

            //cycle cpu? I think we cycle everytime we read from bus

            inc = 1; //increment because data was grabbed from bus
            break;

        case AM_D16:
            {
                uint16_t lo = m_bus->busRead(m_regs.pc);
                //cycle cpu 

                uint16_t hi = m_bus->busRead(m_regs.pc + 1);
                //cycle cpu
                m_fetchData = lo | (hi << 8); //Combine flags 0000 0011 1100 (hi << 8) 
                                            //not actually 4 bits just easier to show technically this is showing hi << 2 
                                            //(or operation just changes any 0's to 1's)
                inc = 2; //increment 2 because we read 2 bytes from bus
            }
            break;
        
        default:
            std::cerr << "Unknown addressing mode" << std::endl;
            break;

    }

    m_regs.pc += inc;
}

bool CPU::cpuStep()
{
    if(!m_halted){
        uint16_t pc = m_regs.pc;

        //--------------------------------------
        //CPU Steps
        // [Fetch] - Fetch instruction and data
        // [Decode] - get instruction process?
        // [Execute] - run instruction process?
        //--------------------------------------

        // [Fetch]
        fetchInstruction();
        fetchData();

        std::cout << "----------------------------------------------------------------" << std::endl;
        std::cout << "Fetching Instruction: " << std::format("{:#x}", pc) << std::endl;
        std::cout << "Current OP Code: " << std::format("{:#x}", m_curOPCode) << std::endl;
        std::cout << "Current Instruction: " << m_curInst << std::endl;
        std::cout << "----------------------------------------------------------------" << std::endl;

    }

    return true;
}

uint16_t CPU::readReg(RegType rt)
{
    switch(rt){
        case RT_A: return m_regs.a; //8 bit regs are okay, but 16 bit will need to combine
        case RT_B: return m_regs.b;
        case RT_C: return m_regs.c;
        case RT_D: return m_regs.d;
        case RT_E: return m_regs.e;
        case RT_F: return m_regs.f;
        case RT_H: return m_regs.h;
        case RT_L: return m_regs.l;
        //case RT_AF: return combine A and F registers (what endian? what is reverse)
        default: return 0;
    }
}