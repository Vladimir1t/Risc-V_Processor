#ifndef RISC_PROC_HPP
#define RISC_PROC_HPP

#include <iostream>
#include <vector>
#include <cstdint>

// class decoder - decode 
// class simulator - execute (изменить текущее состояние)
// write back 
//
// std::vector<char> - для памяти 
// int32_t
// advanced_pc (pc += 1)

namespace Risc_v {

namespace Registors {

const int32_t Default_ = 0xDEAD;

struct Registor {
    const std::string name;
    int32_t           value;
    char              code;
};

// либо сделать хеш таблицу

std::vector<Registor> registors = {  // vector of registors
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
            {"x10", Default_, 0xA},  // func argument
            {"x11", Default_, 0xB},  // func argument
            {"x12", Default_, 0xC},  // func argument
            {"x13", Default_, 0xD},  // func argument
            {"x14", Default_, 0xE},  // func argument
            {"x15", Default_, 0xF},  // func argument
            {"x16", Default_, 0X10}, // func argument
            {"x17", Default_, 0x11}, // func argument
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
            {"pc",  0},  
};
  
}
class Decoder {

public:

const int32_t Default_instr = 0;  // 00...0

static const int32_t R_type_mask = 0x33; // 0110011
static const int32_t I_type_mask = 0x13; // 0010011
static const int32_t S_type_mask = 0x23; // 0100011
static const int32_t B_type_mask = 0x63; // 1100011

struct Instr {
    const int32_t Mask;
    void (Risc_v::Decoder::* func)(int32_t, int32_t, int32_t, int32_t);
};

public:

// void decode_R_type(int32_t) {}
// void decode_I_type(int32_t) {}
// void decode_S_type(int32_t) {}
// void decode_B_type(int32_t) {}

// void add (int32_t, int32_t, int32_t, int32_t);
// void sub (int32_t, int32_t, int32_t, int32_t);
// void and_(int32_t, int32_t, int32_t, int32_t);
// void or_ (int32_t, int32_t, int32_t, int32_t);
// void sll (int32_t, int32_t, int32_t, int32_t);
// void sltu(int32_t, int32_t, int32_t, int32_t);
// void xor_(int32_t, int32_t, int32_t, int32_t);
// void sra (int32_t, int32_t, int32_t, int32_t);
// void slt (int32_t, int32_t, int32_t, int32_t);
// void srl (int32_t, int32_t, int32_t, int32_t);

// void addi (int32_t);
// void andi (int32_t);
// void ori  (int32_t);
// void slli (int32_t);
// void xori (int32_t);
// void srai (int32_t);
// void slti (int32_t);
// void sltiu(int32_t);

// const std::array<Instr, 4> instr_array = {
//     Instr{R_type_mask, decode_R_type},
//     Instr{I_type_mask, decode_I_type},
//     Instr{S_type_mask, decode_S_type},
//     Instr{B_type_mask, decode_B_type}
// };

const std::array<Instr, 10> instr_R_array = {
    Instr{0x40000033, &Risc_v::Decoder::sub},
    Instr{0x40005033, &Risc_v::Decoder::sra},
    Instr{0x33,       &Risc_v::Decoder::add},
    Instr{0x7033,     &Risc_v::Decoder::and_},
    Instr{0x6033,     &Risc_v::Decoder::or_},
    Instr{0x1033,     &Risc_v::Decoder::sll},
    Instr{0x3033,     &Risc_v::Decoder::sltu},
    Instr{0x2033,     &Risc_v::Decoder::slt},
    Instr{0x4033,     &Risc_v::Decoder::xor_},
    Instr{0x5033,     &Risc_v::Decoder::srl}
};

 const std::array<Instr, 8> instr_I_array = {
    Instr{0x7013, &Risc_v::Decoder::andi},
    Instr{0x6013, &Risc_v::Decoder::ori},
    Instr{0x4013, &Risc_v::Decoder::xori},
    Instr{0x2013, &Risc_v::Decoder::slti},
    Instr{0x1013, &Risc_v::Decoder::slli},
    Instr{0x5013, &Risc_v::Decoder::srai},
    Instr{0x3013, &Risc_v::Decoder::sltiu},
    Instr{0x13,   &Risc_v::Decoder::addi}
 };

void decode_R_type(int32_t instr_code) {

    std::cout << "R_type\n";

    for (auto& instr: instr_R_array) {

        if (instr.Mask == (instr_code & instr.Mask)) {
            #ifndef NDEBUG
            std::cout << "Instr code: " << instr.Mask << std::endl;
            #endif
            const int32_t Mask = 0x1F;

            int32_t reg_1 = (instr_code >> 7) & Mask;
            std::cout << "reg_1 = " << reg_1 << std::endl;

            int32_t reg_2 = (instr_code >> 15) & Mask;
            std::cout << "reg_2 = " << reg_2 << std::endl;

            int32_t reg_3 = (instr_code >> 20) & Mask;
            std::cout << "reg_3 = " << reg_3 << std::endl;
            (this->*instr.func)(instr_code, reg_1, reg_2, reg_3);
            break;
        }
    }

}
void decode_I_type(int32_t instr_code) {

    std::cout << "I_type\n";

    for (auto& instr: instr_I_array) {

        if (instr.Mask == (instr_code & instr.Mask)) {
            #ifndef NDEBUG
            std::cout << "Instr code: " << instr.Mask << std::endl;
            #endif
            const int32_t Mask = 0x1F;

            int32_t reg_1 = (instr_code >> 7) & Mask;
            std::cout << "reg_1 = " << reg_1 << std::endl;

            int32_t reg_2 = (instr_code >> 15) & Mask;
            std::cout << "reg_2 = " << reg_2 << std::endl;

            int32_t im = instr_code >> 20; 
            std::cout << "Im = " << im << std::endl;
            (this->*instr.func)(instr_code, reg_1, reg_2, im);
            break;
        }
    }

}
void decode_S_type(int32_t instr_code) const {

}
void decode_B_type(int32_t instr_code) const {

}

void add(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value + Registors::registors.at(reg_3).value;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}

void sub(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {

    std::cout << "sub\n";
    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value - Registors::registors.at(reg_3).value;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void and_(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value & Registors::registors.at(reg_3).value;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void or_(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value | Registors::registors.at(reg_3).value;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void sll(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value << Registors::registors.at(reg_3).value;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void sra(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {  // c сохр знака!

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value >> Registors::registors.at(reg_3).value;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';

}
void sltu(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) { 

    Registors::registors.at(reg_1).value = static_cast<unsigned int>(Registors::registors.at(reg_2).value) < 
                                           static_cast<unsigned int>(Registors::registors.at(reg_3).value);
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void srl(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) { // без сохр знака

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value >> Registors::registors.at(reg_3).value;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void xor_(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value ^ Registors::registors.at(reg_3).value;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void slt(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value < Registors::registors.at(reg_3).value;     
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';   
}


void addi(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value + im;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void andi(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value & im;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void ori(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value | im;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void slli(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value << im;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void srai(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) {  // c сохр знака!

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value >> im;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';

}
void sltiu(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) { 

    Registors::registors.at(reg_1).value = static_cast<unsigned int>(Registors::registors.at(reg_2).value) < 
                                           static_cast<unsigned int>(im);
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void srli(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) { // без сохр знака

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value >> im;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void xori(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value ^ im;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}
void slti(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value < im;     
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';   
}
void decode_instr(int32_t instr_code) {

    const int32_t Mask = 0x7F;
   
    switch((instr_code & Mask))
    {
        case R_type_mask:   
            decode_R_type(instr_code);
            break;
        
        case Decoder::I_type_mask:
            decode_I_type(instr_code);
            break;

        case Decoder::B_type_mask:
            decode_B_type(instr_code);
            break;
        
        case Decoder::S_type_mask:
            decode_S_type(instr_code);
            break;
    }
    Registors::registors.at(32).value += 1;
};
};

class Execute {
public:

// void decode_instr(int32_t instr_code) {

//     Decoder dec;
//     const int32_t Mask = 0x7F;

//     // for (auto& instr: dec.instr_array) {

//     //     if (instr.mask == (instr_code & instr.mask)) {
//     //         std::cout << "find type\n";
//     //         (dec.*(instr.func))(instr_code);        // execute

//     //         Registors::registors.at(32).value += 1; // pc++
//     //         break;
//     //     }
//     // }
//     switch(static_cast<const int32_t>(instr_code & Mask))
//     {
//         case dec.R_type_mask:   
//             dec.decode_R_type(instr_code);
        
//         case dec.I_type_mask:

//     }
//}


};
}

#endif