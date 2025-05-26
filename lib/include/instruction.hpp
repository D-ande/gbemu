#pragma once

#include "common.hpp"

enum AddrMode { //R = general purpose reg (could be 8 bit or 16 bit), 
                //MR = Memory Register? So value will be a memory address? 
                //D8 = instruction is 1 extra byte long 
                //D16 =  instruction is 2 extra bytes long (D16 becomes these values)
    AM_IMP, //
    AM_R_D16, //
    AM_R_R, //
    AM_MR_R, //
    AM_R, //
    AM_R_D8, //
    AM_R_MR, //
    AM_R_HLI,
    AM_R_HLD,
    AM_HLI_R,
    AM_HLD_R,
    AM_R_A8,
    AM_A8_R,
    AM_HL_SPR,
    AM_D16, //
    AM_D8,
    AM_D16_R,
    AM_MR_D8,
    AM_MR,
    AM_A16_R,
    AM_R_A16
};

enum RegType {
    RT_NONE,
    RT_A,
    RT_F,
    RT_B,
    RT_C,
    RT_D,
    RT_E,
    RT_H,
    RT_L,
    RT_AF,
    RT_BC,
    RT_DE,
    RT_HL,
    RT_SP,
    RT_PC
};

enum InType {
    IN_NONE,
    IN_NOP,
    IN_LD,
    IN_INC,
    IN_DEC,
    IN_RLCA,
    IN_ADD,
    IN_RRCA,
    IN_STOP,
    IN_RLA,
    IN_JR,
    IN_RRA,
    IN_DAA,
    IN_CPL,
    IN_SCF,
    IN_CCF,
    IN_HALT,
    IN_ADC,
    IN_SUB,
    IN_SBC,
    IN_AND,
    IN_XOR,
    IN_OR,
    IN_CP,
    IN_POP,
    IN_JP,
    IN_PUSH,
    IN_RET,
    IN_CB,
    IN_CALL,
    IN_RETI,
    IN_LDH,
    IN_JPHL,
    IN_DI,
    IN_EI,
    IN_RST,
    IN_ERR,
    //CB instructions...
    IN_RLC, 
    IN_RRC,
    IN_RL, 
    IN_RR,
    IN_SLA, 
    IN_SRA,
    IN_SWAP, 
    IN_SRL,
    IN_BIT, 
    IN_RES, 
    IN_SET
};

enum CondType{
    CT_NONE, CT_NZ, CT_Z, CT_NC, CT_C
};

class Inst 
{
public:
    InType type;
    AddrMode mode;
    RegType reg1;
    RegType reg2;
    CondType cond;
    uint8_t param;

    Inst(InType type = IN_NONE, AddrMode mode = AM_IMP, RegType reg1 = RT_NONE, RegType reg2 = RT_NONE, CondType cond = CT_NONE, uint8_t param = 0);
    ~Inst();

    friend std::ostream& operator<<(std::ostream& os, const Inst& obj){ 
        os << "Type: " << std::format("{:#x}", (uint8_t)obj.type) 
        << " Mode: " << std::format("{:#x}", (uint8_t)obj.mode) 
        << " Reg1: " << std::format("{:#x}", (uint8_t)obj.reg1) 
        << " Reg2: " << std::format("{:#x}", (uint8_t)obj.reg2) 
        << " Cond: " << std::format("{:#x}", (uint8_t)obj.cond) 
        << " Param: " << std::format("{:#x}", (uint8_t)obj.param); 
        return os; 
    }

    std::string instName(InType t);
};

const std::array<Inst, 0x100> instructionSet = {
    Inst(IN_NOP, AM_IMP),
    Inst(IN_LD, AM_R_D16, RT_BC),
    Inst(IN_LD, AM_MR_R, RT_BC, RT_A),
    Inst(IN_INC, AM_R, RT_BC),
    Inst(IN_INC, AM_R, RT_B),
    Inst(IN_DEC, AM_R, RT_B),
    Inst(IN_LD, AM_R_D8, RT_B),
    Inst(IN_RLCA),
    Inst(IN_LD, AM_A16_R, RT_NONE, RT_SP),
    Inst(IN_ADD, AM_R_R, RT_HL, RT_BC),
    Inst(IN_LD, AM_R_MR, RT_A, RT_BC),
    Inst(IN_DEC, AM_R, RT_BC),
    Inst(IN_INC, AM_R, RT_C),
    Inst(IN_DEC, AM_R, RT_C),
    Inst(IN_LD, AM_R_D8, RT_C),
    Inst(IN_RRCA),

    //0x1X
    Inst(IN_STOP),
    Inst(IN_LD, AM_R_D16, RT_DE),
    Inst(IN_LD, AM_MR_R, RT_DE, RT_A),
    Inst(IN_INC, AM_R, RT_DE),
    Inst(IN_INC, AM_R, RT_D),
    Inst(IN_DEC, AM_R, RT_D),
    Inst(IN_LD, AM_R_D8, RT_D),
    Inst(IN_RLA),
    Inst(IN_JR, AM_D8),
    Inst(IN_ADD, AM_R_R, RT_HL, RT_DE),
    Inst(IN_LD, AM_R_MR, RT_A, RT_DE),
    Inst(IN_DEC, AM_R, RT_DE),
    Inst(IN_INC, AM_R, RT_E),
    Inst(IN_DEC, AM_R, RT_E),
    Inst(IN_LD, AM_R_D8, RT_E),
    Inst(IN_RRA),

    //0x2X
    Inst(IN_JR, AM_D8, RT_NONE, RT_NONE, CT_NZ),
    Inst(IN_LD, AM_R_D16, RT_HL),
    Inst(IN_LD, AM_HLI_R, RT_HL, RT_A),
    Inst(IN_INC, AM_R, RT_HL),
    Inst(IN_INC, AM_R, RT_H),
    Inst(IN_DEC, AM_R, RT_H),
    Inst(IN_LD, AM_R_D8, RT_H),
    Inst(IN_DAA),
    Inst(IN_JR, AM_D8, RT_NONE, RT_NONE, CT_Z),
    Inst(IN_ADD, AM_R_R, RT_HL, RT_HL),
    Inst(IN_LD, AM_R_HLI, RT_A, RT_HL),
    Inst(IN_DEC, AM_R, RT_HL),
    Inst(IN_INC, AM_R, RT_L),
    Inst(IN_DEC, AM_R, RT_L),
    Inst(IN_LD, AM_R_D8, RT_L),
    Inst(IN_CPL),

    //0x3X
    Inst(IN_JR, AM_D8, RT_NONE, RT_NONE, CT_NC),
    Inst(IN_LD, AM_R_D16, RT_SP),
    Inst(IN_LD, AM_HLD_R, RT_HL, RT_A),
    Inst(IN_INC, AM_R, RT_SP),
    Inst(IN_INC, AM_MR, RT_HL),
    Inst(IN_DEC, AM_MR, RT_HL),
    Inst(IN_LD, AM_MR_D8, RT_HL),
    Inst(IN_SCF),
    Inst(IN_JR, AM_D8, RT_NONE, RT_NONE, CT_C),
    Inst(IN_ADD, AM_R_R, RT_HL, RT_SP),
    Inst(IN_LD, AM_R_HLD, RT_A, RT_HL),
    Inst(IN_DEC, AM_R, RT_SP),
    Inst(IN_INC, AM_R, RT_A),
    Inst(IN_DEC, AM_R, RT_A),
    Inst(IN_LD, AM_R_D8, RT_A),
    Inst(IN_CCF),

    //0x4X
    Inst(IN_LD, AM_R_R, RT_B, RT_B),
    Inst(IN_LD, AM_R_R, RT_B, RT_C),
    Inst(IN_LD, AM_R_R, RT_B, RT_D),
    Inst(IN_LD, AM_R_R, RT_B, RT_E),
    Inst(IN_LD, AM_R_R, RT_B, RT_H),
    Inst(IN_LD, AM_R_R, RT_B, RT_L),
    Inst(IN_LD, AM_R_MR, RT_B, RT_HL),
    Inst(IN_LD, AM_R_R, RT_B, RT_A),
    Inst(IN_LD, AM_R_R, RT_C, RT_B),
    Inst(IN_LD, AM_R_R, RT_C, RT_C),
    Inst(IN_LD, AM_R_R, RT_C, RT_D),
    Inst(IN_LD, AM_R_R, RT_C, RT_E),
    Inst(IN_LD, AM_R_R, RT_C, RT_H),
    Inst(IN_LD, AM_R_R, RT_C, RT_L),
    Inst(IN_LD, AM_R_MR, RT_C, RT_HL),
    Inst(IN_LD, AM_R_R, RT_C, RT_A),

    //0x5X
    Inst(IN_LD, AM_R_R,  RT_D, RT_B),
    Inst(IN_LD, AM_R_R,  RT_D, RT_C),
    Inst(IN_LD, AM_R_R,  RT_D, RT_D),
    Inst(IN_LD, AM_R_R,  RT_D, RT_E),
    Inst(IN_LD, AM_R_R,  RT_D, RT_H),
    Inst(IN_LD, AM_R_R,  RT_D, RT_L),
    Inst(IN_LD, AM_R_MR, RT_D, RT_HL),
    Inst(IN_LD, AM_R_R,  RT_D, RT_A),
    Inst(IN_LD, AM_R_R,  RT_E, RT_B),
    Inst(IN_LD, AM_R_R,  RT_E, RT_C),
    Inst(IN_LD, AM_R_R,  RT_E, RT_D),
    Inst(IN_LD, AM_R_R,  RT_E, RT_E),
    Inst(IN_LD, AM_R_R,  RT_E, RT_H),
    Inst(IN_LD, AM_R_R,  RT_E, RT_L),
    Inst(IN_LD, AM_R_MR, RT_E, RT_HL),
    Inst(IN_LD, AM_R_R,  RT_E, RT_A),

    //0x6X
    Inst(IN_LD, AM_R_R,  RT_H, RT_B),
    Inst(IN_LD, AM_R_R,  RT_H, RT_C),
    Inst(IN_LD, AM_R_R,  RT_H, RT_D),
    Inst(IN_LD, AM_R_R,  RT_H, RT_E),
    Inst(IN_LD, AM_R_R,  RT_H, RT_H),
    Inst(IN_LD, AM_R_R,  RT_H, RT_L),
    Inst(IN_LD, AM_R_MR, RT_H, RT_HL),
    Inst(IN_LD, AM_R_R,  RT_H, RT_A),
    Inst(IN_LD, AM_R_R,  RT_L, RT_B),
    Inst(IN_LD, AM_R_R,  RT_L, RT_C),
    Inst(IN_LD, AM_R_R,  RT_L, RT_D),
    Inst(IN_LD, AM_R_R,  RT_L, RT_E),
    Inst(IN_LD, AM_R_R,  RT_L, RT_H),
    Inst(IN_LD, AM_R_R,  RT_L, RT_L),
    Inst(IN_LD, AM_R_MR, RT_L, RT_HL),
    Inst(IN_LD, AM_R_R,  RT_L, RT_A),

    //0x7X
    Inst(IN_LD, AM_MR_R,  RT_HL, RT_B),
    Inst(IN_LD, AM_MR_R,  RT_HL, RT_C),
    Inst(IN_LD, AM_MR_R,  RT_HL, RT_D),
    Inst(IN_LD, AM_MR_R,  RT_HL, RT_E),
    Inst(IN_LD, AM_MR_R,  RT_HL, RT_H),
    Inst(IN_LD, AM_MR_R,  RT_HL, RT_L),
    Inst(IN_HALT),
    Inst(IN_LD, AM_MR_R,  RT_HL, RT_A),
    Inst(IN_LD, AM_R_R,  RT_A, RT_B),
    Inst(IN_LD, AM_R_R,  RT_A, RT_C),
    Inst(IN_LD, AM_R_R,  RT_A, RT_D),
    Inst(IN_LD, AM_R_R,  RT_A, RT_E),
    Inst(IN_LD, AM_R_R,  RT_A, RT_H),
    Inst(IN_LD, AM_R_R,  RT_A, RT_L),
    Inst(IN_LD, AM_R_MR, RT_A, RT_HL),
    Inst(IN_LD, AM_R_R,  RT_A, RT_A),

    //0x8X
    Inst(IN_ADD, AM_R_R, RT_A, RT_B),
    Inst(IN_ADD, AM_R_R, RT_A, RT_C),
    Inst(IN_ADD, AM_R_R, RT_A, RT_D),
    Inst(IN_ADD, AM_R_R, RT_A, RT_E),
    Inst(IN_ADD, AM_R_R, RT_A, RT_H),
    Inst(IN_ADD, AM_R_R, RT_A, RT_L),
    Inst(IN_ADD, AM_R_MR, RT_A, RT_HL),
    Inst(IN_ADD, AM_R_R, RT_A, RT_A),
    Inst(IN_ADC, AM_R_R, RT_A, RT_B),
    Inst(IN_ADC, AM_R_R, RT_A, RT_C),
    Inst(IN_ADC, AM_R_R, RT_A, RT_D),
    Inst(IN_ADC, AM_R_R, RT_A, RT_E),
    Inst(IN_ADC, AM_R_R, RT_A, RT_H),
    Inst(IN_ADC, AM_R_R, RT_A, RT_L),
    Inst(IN_ADC, AM_R_MR, RT_A, RT_HL),
    Inst(IN_ADC, AM_R_R, RT_A, RT_A),

    //0x9X
    Inst(IN_SUB, AM_R_R, RT_A, RT_B),
    Inst(IN_SUB, AM_R_R, RT_A, RT_C),
    Inst(IN_SUB, AM_R_R, RT_A, RT_D),
    Inst(IN_SUB, AM_R_R, RT_A, RT_E),
    Inst(IN_SUB, AM_R_R, RT_A, RT_H),
    Inst(IN_SUB, AM_R_R, RT_A, RT_L),
    Inst(IN_SUB, AM_R_MR, RT_A, RT_HL),
    Inst(IN_SUB, AM_R_R, RT_A, RT_A),
    Inst(IN_SBC, AM_R_R, RT_A, RT_B),
    Inst(IN_SBC, AM_R_R, RT_A, RT_C),
    Inst(IN_SBC, AM_R_R, RT_A, RT_D),
    Inst(IN_SBC, AM_R_R, RT_A, RT_E),
    Inst(IN_SBC, AM_R_R, RT_A, RT_H),
    Inst(IN_SBC, AM_R_R, RT_A, RT_L),
    Inst(IN_SBC, AM_R_MR, RT_A, RT_HL),
    Inst(IN_SBC, AM_R_R, RT_A, RT_A),


    //0xAX
    Inst(IN_AND, AM_R_R, RT_A, RT_B),
    Inst(IN_AND, AM_R_R, RT_A, RT_C),
    Inst(IN_AND, AM_R_R, RT_A, RT_D),
    Inst(IN_AND, AM_R_R, RT_A, RT_E),
    Inst(IN_AND, AM_R_R, RT_A, RT_H),
    Inst(IN_AND, AM_R_R, RT_A, RT_L),
    Inst(IN_AND, AM_R_MR, RT_A, RT_HL),
    Inst(IN_AND, AM_R_R, RT_A, RT_A),
    Inst(IN_XOR, AM_R_R, RT_A, RT_B),
    Inst(IN_XOR, AM_R_R, RT_A, RT_C),
    Inst(IN_XOR, AM_R_R, RT_A, RT_D),
    Inst(IN_XOR, AM_R_R, RT_A, RT_E),
    Inst(IN_XOR, AM_R_R, RT_A, RT_H),
    Inst(IN_XOR, AM_R_R, RT_A, RT_L),
    Inst(IN_XOR, AM_R_MR, RT_A, RT_HL),
    Inst(IN_XOR, AM_R_R, RT_A, RT_A),

    //0xBX
    Inst(IN_OR, AM_R_R, RT_A, RT_B),
    Inst(IN_OR, AM_R_R, RT_A, RT_C),
    Inst(IN_OR, AM_R_R, RT_A, RT_D),
    Inst(IN_OR, AM_R_R, RT_A, RT_E),
    Inst(IN_OR, AM_R_R, RT_A, RT_H),
    Inst(IN_OR, AM_R_R, RT_A, RT_L),
    Inst(IN_OR, AM_R_MR, RT_A, RT_HL),
    Inst(IN_OR, AM_R_R, RT_A, RT_A),
    Inst(IN_CP, AM_R_R, RT_A, RT_B),
    Inst(IN_CP, AM_R_R, RT_A, RT_C),
    Inst(IN_CP, AM_R_R, RT_A, RT_D),
    Inst(IN_CP, AM_R_R, RT_A, RT_E),
    Inst(IN_CP, AM_R_R, RT_A, RT_H),
    Inst(IN_CP, AM_R_R, RT_A, RT_L),
    Inst(IN_CP, AM_R_MR, RT_A, RT_HL),
    Inst(IN_CP, AM_R_R, RT_A, RT_A),

    //0xCX
    Inst(IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_NZ),
    Inst(IN_POP, AM_R, RT_BC),
    Inst(IN_JP, AM_D16, RT_NONE, RT_NONE, CT_NZ),
    Inst(IN_JP, AM_D16),
    Inst(IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_NZ),
    Inst(IN_PUSH, AM_R, RT_BC),
    Inst(IN_ADD, AM_R_D8, RT_A),
    Inst(IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00),
    Inst(IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_Z),
    Inst(IN_RET),
    Inst(IN_JP, AM_D16, RT_NONE, RT_NONE, CT_Z),
    Inst(IN_CB, AM_D8),
    Inst(IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_Z),
    Inst(IN_CALL, AM_D16),
    Inst(IN_ADC, AM_R_D8, RT_A),
    Inst(IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x08),

    //0xDX
    Inst(IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_NC),
    Inst(IN_POP, AM_R, RT_DE),
    Inst(IN_JP, AM_D16, RT_NONE, RT_NONE, CT_NC),
    Inst(),
    Inst(IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_NC),
    Inst(IN_PUSH, AM_R, RT_DE),
    Inst(IN_SUB, AM_R_D8, RT_A),
    Inst(IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x10),
    Inst(IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_C),
    Inst(IN_RETI),
    Inst(IN_JP, AM_D16, RT_NONE, RT_NONE, CT_C),
    Inst(),
    Inst(IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_C),
    Inst(),
    Inst(IN_SBC, AM_R_D8, RT_A),
    Inst(IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x18),

    //0xEX
    Inst(IN_LDH, AM_A8_R, RT_NONE, RT_A),
    Inst(IN_POP, AM_R, RT_HL),
    Inst(IN_LD, AM_MR_R, RT_C, RT_A),
    Inst(),
    Inst(),
    Inst(IN_PUSH, AM_R, RT_HL),
    Inst(IN_AND, AM_R_D8, RT_A),
    Inst(IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x20),
    Inst(IN_ADD, AM_R_D8, RT_SP),
    Inst(IN_JP, AM_R, RT_HL),
    Inst(IN_LD, AM_A16_R, RT_NONE, RT_A),
    Inst(),
    Inst(),
    Inst(),
    Inst(IN_XOR, AM_R_D8, RT_A),
    Inst(IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x28),


    //0xFX
    Inst(IN_LDH, AM_R_A8, RT_A),
    Inst(IN_POP, AM_R, RT_AF),
    Inst(IN_LD, AM_R_MR, RT_A, RT_C),
    Inst(IN_DI),
    Inst(),
    Inst(IN_PUSH, AM_R, RT_AF),
    Inst(IN_OR, AM_R_D8, RT_A),
    Inst(IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x30),
    Inst(IN_LD, AM_HL_SPR, RT_HL, RT_SP),
    Inst(IN_LD, AM_R_R, RT_SP, RT_HL),
    Inst(IN_LD, AM_R_A16, RT_A),
    Inst(IN_EI),
    Inst(),
    Inst(),
    Inst(IN_CP, AM_R_D8, RT_A),
    Inst(IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x38),
};