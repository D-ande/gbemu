#include "instruction.hpp"

// InType type;
// AddrMode mode;
// RegType reg1;
// RegType reg2;
// CondType cond;
// uint8_t param;
Inst::Inst(InType type, AddrMode mode, RegType reg1, RegType reg2, CondType cond, uint8_t param)
{
    this->type = type;
    this->mode = mode;
    this->reg1 = reg1;
    this->reg2 = reg2;
    this->cond = cond;
    this->param = param;
}

Inst::~Inst()
{

}

std::string Inst::instName(InType t)
{
    NOT_IMPL
}