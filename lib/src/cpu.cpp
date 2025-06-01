#include "cpu.hpp"
#include "emu.hpp"

CPU::CPU(Bus *bus) {
  m_bus = bus;
  m_regs.pc = 0x100;
  m_regs.a = 0x01;
}

CPU::~CPU() {}

void CPU::fetchInstruction() {
  // Read addr bus and get the current program counter address opcode

  m_curOPCode = m_bus->busRead(
      m_regs.pc++); // Read instruction will always increment forward 1.
                    // Depending on instruction we may have to increment more
                    // during decode. This will pass pc first and then increment
                    // afterwards.
  m_curInst = instructionSet[m_curOPCode];

  if (m_curInst.type == IN_NONE) {
    std::cerr << "Attempted to fetch NULL instruction: " << m_curInst
              << std::endl;
  }
  // if (m_curOPCode == 0xC3) //Delete this if later when implemented
  // {
  //     m_curInst = Inst(IN_JP, AM_D16);
  // }
  // else if (m_curOPCode > 0x08){
  //     std::cout << "Bad OP code: " << m_curOPCode << std::endl;
  //     //throw std::out_of_range("OP Code not implemented");
  // }
  // else{
  //     m_curInst = instructionSet[m_curOPCode];
  // }
}

void CPU::fetchData() {
  // Check what registers we're interacting with
  m_memDest = 0;
  m_isDestMem = false;
  int inc = 0;

  GbEmu *emu = GbEmu::getInstance();

  // Check pc increment (if 16 bit increment pc twice)
  // if(m_curInst == NULL) { return; } //Need to get data based on what address
  // mode (first is dest, second is source) data we're fetching is the value at
  // source register (second item in AddrMode)

  switch (m_curInst.mode) { // Cycle only when reading from bus, and inc only
                            // when reading from bus
  case AM_IMP:
    break;

  case AM_R:
    // Get R
    m_fetchData = readReg(m_curInst.reg1); // reg1 & reg2 is memory address of
                                           // what register we want to read.
    break;

  case AM_R_R:
    m_fetchData = readReg(m_curInst.reg2); // If both R then source is reg 2
    break;

  case AM_R_D8: // D8 as source tells us to grab the next byte from bus because
                // instruction is longer
  case AM_D8:
    m_fetchData = m_bus->busRead(m_regs.pc);

    // cycle cpu? I think we cycle everytime we read from bus
    emu->cycle(1);

    inc = 1; // increment because data was grabbed from bus
    break;

  case AM_R_D16:
  case AM_D16: {
    uint16_t lo = m_bus->busRead(m_regs.pc);
    // cycle cpu
    emu->cycle(1);

    uint16_t hi = m_bus->busRead(m_regs.pc + 1);
    // cycle cpu
    emu->cycle(1);

    m_fetchData =
        lo |
        (hi
         << 8); // Combine flags 0000 0011 1100 (hi << 8)
                // not actually 4 bits just easier to show technically this is
                // showing hi << 2 (or operation just changes any 0's to 1's)
    inc = 2;    // increment 2 because we read 2 bytes from bus
  } break;

  case AM_MR_R:
    m_fetchData = readReg(m_curInst.reg2);
    m_memDest = readReg(m_curInst.reg1);
    m_isDestMem = true; // Destination is memory address

    if (m_curInst.reg1 == RT_C) // Why do we do this?
    {
      m_memDest |= 0xFF00; // This just makes everything in the first byte 1
    }
    break;

  case AM_R_MR: // Register holds address on bus we want to read for data
  {
    uint16_t addr = readReg(m_curInst.reg2);

    if (m_curInst.reg2 == RT_C) {
      addr |= 0xFF00; // This just makes everything in the first byte 1
    }

    m_fetchData = m_bus->busRead(
        addr); // We don't increase because we're pulling a direct address
    // cycle because read from bus
    emu->cycle(1);
    break;
  }

  default:
    if (m_curInst.mode > 20) {
      std::cerr << "Unknown addressing mode: " << (uint8_t)m_curInst.mode
                << std::endl;
      throw std::out_of_range("Attempting to access non existing address mode");
    } else {
      std::cerr << "Address Mode " << (uint8_t)m_curInst.mode
                << " Not Implemented" << std::endl;
    }
    break;
  }

  m_regs.pc += inc;
}

void CPU::execute() {
  switch (m_curInst.type) {
  case IN_NONE:
    proc_none();
    break;
  case IN_NOP:
    proc_nop();
    break;
  case IN_LD:
    proc_ld();
    break;
  default:
    std::cerr << "Unhandled Instruction Type" << std::endl;
    break;
  }
}

bool CPU::cpuStep() {
  if (!m_halted) {
    uint16_t pc = m_regs.pc;

    //--------------------------------------
    // CPU Steps
    // [Fetch] - Fetch instruction and data
    // [Decode] - get instruction process?
    // [Execute] - run instruction process?
    //--------------------------------------

    // [Fetch]
    fetchInstruction();
    fetchData();

    // std::cout <<
    // "----------------------------------------------------------------" <<
    // std::endl; std::cout << "Fetching Instruction: " << std::format("{:#x}",
    // pc) << std::endl; std::cout << "Current OP Code: " <<
    // std::format("{:#x}", m_curOPCode) << std::endl; std::cout << "Current
    // Instruction: " << m_curInst << std::endl; std::cout <<
    // "----------------------------------------------------------------" <<
    // std::endl;

    // [Execute]
    execute();
  }

  return true;
}

uint16_t CPU::readReg(RegType rt) {
  switch (rt) {
  case RT_A:
    return m_regs.a; // 8 bit regs are okay, but 16 bit will need to combine
  case RT_F:
    return m_regs.f;
  case RT_B:
    return m_regs.b;
  case RT_C:
    return m_regs.c;
  case RT_D:
    return m_regs.d;
  case RT_E:
    return m_regs.e;
  case RT_H:
    return m_regs.h;
  case RT_L:
    return m_regs.l;
  case RT_AF:
    return htons(
        *(uint16_t *)&m_regs
             .a); // combine A and F registers so we access register f
                  // because we're taking a 16 bit value pointer (memory goes
                  // beyond 8 bit a) using htons because host to network we're
                  // reading reg doesn't really matter if we use htons or ntohs
                  // A and F are next to eachother in struct so accessing a this
                  // way will give f
  case RT_BC:
    return htons(*(uint16_t *)&m_regs.b);
  case RT_DE:
    return htons(*(uint16_t *)&m_regs.d);
  case RT_HL:
    return htons(*(uint16_t *)&m_regs.h);

  case RT_PC:
    return m_regs.pc;
  case RT_SP:
    return m_regs.sp;

  default:
    return 0;
  }
}

void CPU::setReg(RegType rt, uint16_t val) {
  switch (rt) {
  case RT_A:
    m_regs.a = val & 0xFF;
    break; // Taking 16 bit but only first byte & with 0xFF ignores 2nd byte;
  case RT_F:
    m_regs.f = val & 0xFF;
    break;
  case RT_B:
    m_regs.b = val & 0xFF;
    break;
  case RT_C:
    m_regs.c = val & 0xFF;
    break;
  case RT_D:
    m_regs.d = val & 0xFF;
    break;
  case RT_E:
    m_regs.e = val & 0xFF;
    break;
  case RT_H:
    m_regs.h = val & 0xFF;
    break;
  case RT_L:
    m_regs.l = val & 0xFF;
    break;

  case RT_AF:
    *(uint16_t *)&m_regs.a = ntohs(val);
    break; // ntohs because cpu is receiving data
  case RT_BC:
    *(uint16_t *)&m_regs.b = ntohs(val);
    break;
  case RT_DE:
    *(uint16_t *)&m_regs.d = ntohs(val);
    break;
  case RT_HL:
    *(uint16_t *)&m_regs.h = ntohs(val);
    break;

  case RT_PC:
    m_regs.pc = val;
    break;
  case RT_SP:
    m_regs.pc = val;
    break;
  default:
    break;
  }
}
