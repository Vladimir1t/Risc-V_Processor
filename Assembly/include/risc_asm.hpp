#ifndef RISC_ASM_HPP
#define RISC_ASM_HPP

#include <iostream>
#include <vector>

/* ISA */
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
        {"XLEN",   Default_},
        {"XLEN-1", Default_},
        {"pc",     Default_},
}; 
}

namespace Instruction {

const int Default_instr = 0;  // 00...0

struct Command {
    const std::string name;
    void (*func)(std::ifstream&, std::ofstream&);
};

void add  (std::ifstream&, std::ofstream&);
void sub  (std::ifstream&, std::ofstream&);
void sltu (std::ifstream&, std::ofstream&);
void and_ (std::ifstream&, std::ofstream&);
void or_  (std::ifstream&, std::ofstream&);
void xor_ (std::ifstream&, std::ofstream&);
void sll  (std::ifstream&, std::ofstream&);
void slt  (std::ifstream&, std::ofstream&);
void sltu (std::ifstream&, std::ofstream&);
void srl  (std::ifstream&, std::ofstream&);
void sra  (std::ifstream&, std::ofstream&);

void addi (std::ifstream&, std::ofstream&);
void andi (std::ifstream&, std::ofstream&);
void ori  (std::ifstream&, std::ofstream&);
void xori (std::ifstream&, std::ofstream&);
void slli (std::ifstream&, std::ofstream&);
void slti (std::ifstream&, std::ofstream&);
void srai (std::ifstream&, std::ofstream&);
void sltiu(std::ifstream&, std::ofstream&);

void R_type_instr(std::ifstream& asm_file, std::ofstream& bytecode, 
    const int com_code);
void I_type_instr(std::ifstream& asm_file, std::ofstream& bytecode, 
    const int com_code);

std::vector<Command> commands = {
    {"add",  add},
    {"sub",  sub},
    {"sltu", sltu},

    {"and",  and_},
    {"or",   or_},
    {"xor",  xor_},
    {"sll",  sll},
    {"slt",  slt},
    {"srl",  srl},
    {"sra",  sra},

    {"addi",  addi},
    {"andi",  andi},
    {"ori",   ori},
    {"xori",  xori},
    {"slti",  slti},
    {"slli",  slli},
    {"srai",  srai},
    {"sltiu", sltiu},

    {"sb", } 
};

void R_type_instr(std::ifstream& asm_file, std::ofstream& bytecode, 
    const int com_code) {
  
    int inst_code = Default_instr | com_code;

    std::string reg1, reg2, reg3;
    asm_file >> reg1 >> reg2 >> reg3;
    reg1.resize(reg1.size() - 1); // delete comma
    reg2.resize(reg2.size() - 1); // delete comma

    std::cout << reg1 << ' ' << reg2 << ' ' << reg3 << '\n';

    for (auto reg: Registors::registors) {
        if (reg.name == reg1) {
            int reg_code = Default_instr;
            reg_code = (reg_code | reg.code) << 7;

            inst_code = inst_code | reg_code;
            #ifndef NDEBUG
                std::cout << "inst code (3) " << inst_code << '\n';
            #endif
            break;
        }
    }
    for (auto reg: Registors::registors) {
        if (reg.name == reg2) {
            int reg_code = Default_instr;
            reg_code = (reg_code | reg.code) << 15;

            inst_code = inst_code | reg_code;
            #ifndef NDEBUG
                std::cout << "inst code (2) " << inst_code << '\n';
            #endif
            break;
        }
    }
    for (auto reg: Registors::registors) {
        if (reg.name == reg3) {
            int reg_code = Default_instr;
            reg_code = (reg_code | reg.code) << 20;

            inst_code = inst_code | reg_code;
            #ifndef NDEBUG
                std::cout << "inst code (3) " << inst_code << '\n';
            #endif
            break;
        }
    }

    bytecode.write(reinterpret_cast<const char*>(&inst_code), sizeof(inst_code));
}

void add(std::ifstream& file_asm, std::ofstream& bytecode) {

    R_type_instr(file_asm, bytecode, 0x33);
}
void sub(std::ifstream& asm_file, std::ofstream& bytecode) {

    R_type_instr(asm_file, bytecode, 0x40000033);
}
void and_(std::ifstream& asm_file, std::ofstream& bytecode) {

    R_type_instr(asm_file, bytecode, 0x7033);
}
void or_(std::ifstream& asm_file, std::ofstream& bytecode) {

    R_type_instr(asm_file, bytecode, 0x6033);
}
void sll(std::ifstream& asm_file, std::ofstream& bytecode) {

    R_type_instr(asm_file, bytecode, 0x1033);
}
void sra(std::ifstream& asm_file, std::ofstream& bytecode) {

    R_type_instr(asm_file, bytecode, 0x40005033);
}
void sltu(std::ifstream& asm_file, std::ofstream& bytecode) {

    R_type_instr(asm_file, bytecode, 0x3033);
}
void slt(std::ifstream& asm_file, std::ofstream& bytecode) {

    R_type_instr(asm_file, bytecode, 0x2033);
}
void xor_(std::ifstream& asm_file, std::ofstream& bytecode) {

    R_type_instr(asm_file, bytecode, 0x4033);
}
void srl(std::ifstream& asm_file, std::ofstream& bytecode) {

    R_type_instr(asm_file, bytecode, 0x5033);
}

void I_type_instr(std::ifstream& asm_file, std::ofstream& bytecode, 
    const int com_code) {

    int inst_code = Default_instr | com_code;

    std::string reg1, reg2;
    short       num;

    asm_file >> reg1 >> reg2 >> num;
    reg1.resize(reg1.size() - 1); // delete comma
    reg2.resize(reg2.size() - 1); // delete comma

    std::cout << reg1 << ' ' << reg2 << ' ' << num << '\n';

    for (auto reg: Registors::registors) {
        if (reg.name == reg1) {
            int reg_code = Default_instr;
            reg_code = (reg_code | reg.code) << 7;

            inst_code = inst_code | reg_code;
            #ifndef NDEBUG
                std::cout << "inst code (1) " << inst_code << '\n';
            #endif
            break;
        }
    }
    for (auto reg: Registors::registors) {
        if (reg.name == reg2) {
            int reg_code = Default_instr;
            reg_code = (reg_code | reg.code) << 15;

            inst_code = inst_code | reg_code;
            #ifndef NDEBUG
                std::cout << "inst code (2) " << inst_code << '\n';
            #endif
            break;
        }
    }

    int num_code = Default_instr;
    num_code = (num_code | num) << 20;
    inst_code = inst_code | num_code;
    #ifndef NDEBUG
        std::cout << "inst code (3) " << inst_code << '\n';
    #endif

    bytecode.write(reinterpret_cast<const char*>(&inst_code), 
        sizeof(inst_code));
}


void addi(std::ifstream& asm_file, std::ofstream& bytecode) {

    I_type_instr(asm_file, bytecode, 0x13);
}

void andi(std::ifstream& asm_file, std::ofstream& bytecode) {

    I_type_instr(asm_file, bytecode, 0x7013);
}
void ori(std::ifstream& asm_file, std::ofstream& bytecode) {

    I_type_instr(asm_file, bytecode, 0x6013);
}
void xori(std::ifstream& asm_file, std::ofstream& bytecode) {

    I_type_instr(asm_file, bytecode, 0x4013);
}
void slti(std::ifstream& asm_file, std::ofstream& bytecode) {

    I_type_instr(asm_file, bytecode, 0x2013);
}
void slli(std::ifstream& asm_file, std::ofstream& bytecode) {

    I_type_instr(asm_file, bytecode, 0x1013);
}
void srai(std::ifstream& asm_file, std::ofstream& bytecode) {

    I_type_instr(asm_file, bytecode, 0x5013);
}
void sltiu(std::ifstream& asm_file, std::ofstream& bytecode) {

    I_type_instr(asm_file, bytecode, 0x3013);
}
}

// namespace Risc_v {

// class Asm {

// private:


// public:

// };


// }

#endif 