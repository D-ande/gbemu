#include "cpu.hpp"

void CPU::proc_ld() {
  std::cout << "Load Instruction Processed" << std::endl;
  if (m_isDestMem) {
    // copy source to memory address on bus?
    // If writing to bus cycle
    // Need to check if destination is 8 bit or 16 bit
  }
}

void CPU::proc_none() {
  std::cerr << "INVALID INSTRUCTION" << std::endl;
  return;
}

void CPU::proc_nop() {
  std::cout << "NOP Instruction Processed" << std::endl;
  // Do Nothing?
}
