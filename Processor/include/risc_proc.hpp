#ifndef RISC_PROC_HPP
#define RISC_PROC_HPP

#include <iostream>
#include <vector>

// class decoder - decode 
// class simulator - execute (изменить текущее состояние)
// write back 
//
// std::vector<char> - для памяти 
// int32_t
// advanced_pc (pc += 1)

namespace Risc_v {

namespace Registors {

const int Default_ = 0xDEAD;

struct Registor {
    const std::string name;
    int               value;
    char              code;
};

std::vector<Registor> registors = {
            {"x0",  0,        0x0},  // zero
            {"x1",  Default_, 0x1},  // return addres
            {"x2",  Default_, 0x2},  // stack pointer
            {"x3",  Default_, 0x3},  // global pointer
            {"x4",  Default_, 0x4},  // thread pointer
            {"x5",  Default_, 0x5},  // temporary
            {"x6",  Default_, 0x6},  // temporary
            {"x7",  Default_, 0x7},  // temporary
            {"x8",  Default_, 0x8},  //
            {"x9",  Default_, 0x9},
            {"x10", Default_, 0xA},
            {"x11", Default_, 0xB},
            {"x12", Default_, 0xC},
            {"x13", Default_, 0xD},
            {"x14", Default_, 0xE},
            {"x15", Default_, 0xF},
            {"x16", Default_, 0X10},
            {"x17", Default_, 0x11},
            {"x18", Default_, 0x12},
            {"x19", Default_, 0x13},
            {"x20", Default_, 0x14},
            {"x21", Default_, 0x15},
            {"x22", Default_, 0x16},
            {"x23", Default_, 0x17},
            {"x24", Default_, 0x18},
            {"x25", Default_, 0x19},
            {"x26", Default_, 0x1A},
            {"x27", Default_, 0x1B},
            {"x28", Default_, 0x1C},
            {"x29", Default_, 0x1D},
            {"x30", Default_, 0x1E},
            {"x31", Default_, 0x1F},
            {"pc",     0},
};
  
}
namespace Instruction {

const int Default_instr = 0;  // 00...0

const int R_type_mask = 0x33; // 0110011
const int I_type_mask = 0x13; // 0010011
const int S_type_mask = 0x23; // 0100011
const int B_type_mask = 0x63; // 1100011

struct Instr {
    const int mask;
    void (*func)(int);
};

void decode_R_type(int);
void decode_I_type(int);
void decode_S_type(int);
void decode_B_type(int);

void add (int);
void sub (int);
void and_(int);
void or_ (int);
void sll (int);
void sltu(int);
void xor_(int);
void sra (int);
void slt (int);
void srl (int);

void addi (int);
void andi (int);
void ori  (int);
void slli (int);
void xori (int);
void srai (int);
void slti (int);
void sltiu(int);

const std::vector<Instr> instr_array = {
    {R_type_mask, decode_R_type},
    {I_type_mask, decode_I_type},
    {S_type_mask, decode_S_type},
    {B_type_mask, decode_B_type}
};

const std::vector<Instr> instr_R_array = {
    {0x33,       add},
    {0x40000033, sub},
    {0x7033,     and_},
    {0x6033,     or_},
    {0x1033,     sll},
    {0x40005033, sra},
    {0x3033,     sltu},
    {0x2033,     slt},
    {0x4033,     xor_},
    {0x5033,     srl},
};

const std::vector<Instr> instr_I_array = {
    {0x13,   addi},
    {0x7013, andi},
    {0x6013, ori},
    {0x4013, xori},
    {0x2013, slti},
    {0x1013, slli},
    {0x5013, srai},
    {0x3013, sltiu}

};

void decode_R_type(int instr_code) {


}

void decode_I_type(int instr_code) {

}
void decode_S_type(int instr_code) {

}
void decode_B_type(int instr_code) {

}
}


class Proc {

private:


public:

void decode_instr(int instr_code) {

    for (auto instr: Instruction::instr_array) {
    
        if (instr.mask == (instr_code & instr.mask)) {
            std::cout << "find type\n";
            instr.func(instr_code);
            
            Registors::registors.at(32).value += 1; // pc++
            break;
        }
    }
    
}


};
}

#endif