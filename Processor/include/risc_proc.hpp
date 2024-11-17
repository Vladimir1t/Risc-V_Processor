#ifndef RISC_PROC_HPP
#define RISC_PROC_HPP

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdint>

// class decoder - decode (ok)
// class simulator - execute (изменить текущее состояние)
// write back 
//
// std::vector<char> - для памяти (ok)
// int32_t (ok)
// advanced_pc (pc += 1) (ok)
// ecall
// ebreak
// добавить S-format: запись в память
// В-format: ветвления
// U-format: 
// 

namespace Risc_v {

namespace Registors {

const int32_t Default_ = 0x1;

struct Registor {
    const std::string name;
    int32_t           value;
    char              code;
};

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
namespace RAM {

std::vector<char> Ram(200, 0); 

}

class Decoder {

public:

const int32_t Default_instr = 0;  // 00...0

static const int32_t B_type_mask = 0x63; // 1100011
static const int32_t R_type_mask = 0x33; // 0110011
static const int32_t S_type_mask = 0x23; // 0100011
static const int32_t I_type_mask = 0x13; // 0010011
static const int32_t L_type_mask = 0x3;  // 0000011

struct Instr {
    const int32_t Mask;
    void (Risc_v::Decoder::* func)(int32_t, int32_t, int32_t, int32_t);
};

public:

const std::array<Instr, 10> instr_R_array = {
    Instr{0x40005033, &Risc_v::Decoder::sra },
    Instr{0x40000033, &Risc_v::Decoder::sub },
    Instr{0x7033,     &Risc_v::Decoder::and_},
    Instr{0x6033,     &Risc_v::Decoder::or_ },
    Instr{0x5033,     &Risc_v::Decoder::srl },
    Instr{0x4033,     &Risc_v::Decoder::xor_},
    Instr{0x3033,     &Risc_v::Decoder::sltu},
    Instr{0x2033,     &Risc_v::Decoder::slt },
    Instr{0x1033,     &Risc_v::Decoder::sll },
    Instr{0x33,       &Risc_v::Decoder::add }
};

const std::array<Instr, 8> instr_I_array = {
    Instr{0x7013, &Risc_v::Decoder::andi },
    Instr{0x6013, &Risc_v::Decoder::ori  },
    Instr{0x5013, &Risc_v::Decoder::srai },
    Instr{0x4013, &Risc_v::Decoder::xori },
    Instr{0x3013, &Risc_v::Decoder::sltiu},
    Instr{0x2013, &Risc_v::Decoder::slti },
    Instr{0x1013, &Risc_v::Decoder::slli },
    Instr{0x13,   &Risc_v::Decoder::addi }
};
const std::array<Instr, 5> instr_L_array = {
    Instr{0x5003, &Risc_v::Decoder::lhu}, 
    Instr{0x4003, &Risc_v::Decoder::lbu},
    Instr{0x2003, &Risc_v::Decoder::lw },
    Instr{0x1003, &Risc_v::Decoder::lh },
    Instr{0x3,    &Risc_v::Decoder::lb },
};
const std::array<Instr, 3> instr_S_array = {
    Instr{0x2023, &Risc_v::Decoder::sw},
    Instr{0x1023, &Risc_v::Decoder::sh},
    Instr{0x23,   &Risc_v::Decoder::sb}, 
};
const std::array<Instr, 6> instr_B_array = {
    Instr{0x5063, &Risc_v::Decoder::bgeu},
    Instr{0x4063, &Risc_v::Decoder::bltu},
    Instr{0x3063, &Risc_v::Decoder::bge},
    Instr{0x2063, &Risc_v::Decoder::blt},
    Instr{0x1063, &Risc_v::Decoder::bne},
    Instr{0x63,   &Risc_v::Decoder::beq}, 
};

void decode_instr(int32_t instr_code) {

    const int32_t Mask = 0x7F;
   
    switch((instr_code & Mask))
    {
        case Decoder::B_type_mask:
            decode_B_type(instr_code);
            break;
        
        case Decoder::R_type_mask:   
            decode_R_type(instr_code);
            break;
        
        case Decoder::S_type_mask:
            decode_S_type(instr_code);
            break;

        case Decoder::I_type_mask:
            decode_I_type(instr_code);
            break;

        case Decoder::L_type_mask:
            decode_L_type(instr_code);
            break;
    }
    Registors::registors.at(32).value += 1;
}

void decode_R_type(int32_t instr_code) {

    std::cout << "R_type\n";

    for (auto& instr: instr_R_array) {

        if (instr.Mask == (instr_code & instr.Mask)) {
            #ifndef NDEBUG
                std::cout << "Instr code: " << instr.Mask << std::endl;
            #endif
            const int32_t Mask = 0x1F;

            int32_t reg_1 = (instr_code >> 7) & Mask;

            int32_t reg_2 = (instr_code >> 15) & Mask;

            int32_t reg_3 = (instr_code >> 20) & Mask;
            #ifndef NGEBUG
                std::cout << "reg_1 = " << reg_1 << std::endl;
                std::cout << "reg_2 = " << reg_2 << std::endl;
                std::cout << "reg_3 = " << reg_3 << std::endl;
            #endif
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

            int32_t reg_2 = (instr_code >> 15) & Mask;

            int32_t im = instr_code >> 20; 
            #ifndef NGEBUG
                std::cout << "reg_1 = " << reg_1 << std::endl;
                std::cout << "reg_2 = " << reg_2 << std::endl;
                std::cout << "Im = " << im << std::endl;
            #endif
            (this->*instr.func)(instr_code, reg_1, reg_2, im);
            break;
        }
    }
}

void decode_L_type(int32_t instr_code) {

    std::cout << "L_type\n";

    for (auto& instr: instr_L_array) {

        if (instr.Mask == (instr_code & instr.Mask)) {
            #ifndef NDEBUG
                std::cout << "Instr code: " << instr.Mask << std::endl;
            #endif
            const int32_t Mask = 0x1F; // 111111

            int32_t reg_res = (instr_code >> 7) & Mask;

            int32_t reg_adr = (instr_code >> 15) & Mask;

            int32_t im = instr_code >> 20; 
            #ifndef NGEBUG
                std::cout << "reg_res = " << reg_res << std::endl;
                std::cout << "reg_adr = " << reg_adr << std::endl;
                std::cout << "Im = " << im << std::endl;
            #endif
            (this->*instr.func)(instr_code, reg_res, reg_adr, im);
            break;
        }
    }
}
void decode_S_type(int32_t instr_code) {

    std::cout << "S_type\n";

    for (auto& instr: instr_S_array) {

        if (instr.Mask == (instr_code & instr.Mask)) {
            #ifndef NDEBUG
                std::cout << "Instr code: " << instr.Mask << std::endl;
            #endif
            const int32_t Mask = 0x1F; // 111111

            int32_t reg_from = (instr_code >> 7) & Mask;

            int32_t reg_adr = (instr_code >> 15) & Mask;

            int32_t im = instr_code >> 20; 
            #ifndef NGEBUG
                std::cout << "reg_from = " << reg_from << std::endl;
                std::cout << "reg_adr = " << reg_adr << std::endl;
                std::cout << "Im = " << im << std::endl;
            #endif
            (this->*instr.func)(instr_code, reg_from, reg_adr, im);
            break;
        }
    }
}
void decode_B_type(int32_t instr_code) {

    std::cout << "B_type\n";

    for (auto& instr: instr_B_array) {

        if (instr.Mask == (instr_code & instr.Mask)) {
            #ifndef NDEBUG
                std::cout << "Instr code: " << instr.Mask << std::endl;
            #endif
            const int32_t Mask = 0x1F;  // 111111

            int32_t reg_1 = (instr_code >> 15) & Mask;

            int32_t reg_2 = (instr_code >> 20) & Mask;

            int32_t im = 0;
            im = (im | ((instr_code & 0x80) << 3));         // im[11]
            im = (im | ((instr_code & 0x7E000000) >> 21));  // im[10-5]
            im = (im | ((instr_code & 0xF00) >> 7));        // im[4-1]

            if (((instr_code & 0x80000000) >> 31) == 1)     //im[12]
                im = im | 0xFFFFF800;    
            #ifndef NGEBUG       
                std::cout << "  reg_1 = " << reg_1 << std::endl;
                std::cout << "  reg_2 = " << reg_2 << std::endl;
                std::cout << "  im[1] " << im << ' ' << (instr_code & 0x80) << std::endl; 
                std::cout << "  im[2] " << im << ' ' << (instr_code & 0x7E000000) << std::endl; 
                std::cout << "  im[3] " << im << ' ' << (instr_code & 0xF00) << std::endl; 
                std::cout << "  Im = " << im << std::endl;
            #endif 
            (this->*instr.func)(instr_code, reg_1, reg_2, im);
            break;
        }
    }
}
void decode_U_type(int32_t instr_code) const {

}
void decode_J_type(int32_t instr_code) const {

}

void add(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {

    Registors::registors.at(reg_1).value = Registors::registors.at(reg_2).value + Registors::registors.at(reg_3).value;
    std::cout << "result = " << Registors::registors.at(reg_1).value << '\n';
}

void sub(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t reg_3) {

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


void lb(int32_t instr_code, int32_t reg_res, int32_t reg_adr, int32_t im) {

    Registors::registors.at(reg_res).value = static_cast<int32_t>(RAM::Ram.at(Registors::registors.at(reg_adr).value + im));  //?   
    std::cout << "[lb] result = " << Registors::registors.at(reg_res).value << '\n';   
}
void lh(int32_t instr_code, int32_t reg_res, int32_t reg_adr, int32_t im) {

    uint16_t* ptr = reinterpret_cast<uint16_t*>(RAM::Ram.data() + Registors::registors.at(reg_adr).value + im);
    Registors::registors.at(reg_res).value = static_cast<int32_t>(*ptr);     
    std::cout << "[lh] result = " << Registors::registors.at(reg_res).value << '\n';   
}
void lw(int32_t instr_code, int32_t reg_res, int32_t reg_adr, int32_t im) {

    int32_t* ptr = reinterpret_cast<int32_t*>(RAM::Ram.data() + Registors::registors.at(reg_adr).value + im);
    Registors::registors.at(reg_res).value = static_cast<int32_t>(*ptr);        
    std::cout << "[lw] result = " << Registors::registors.at(reg_res).value << '\n';   
}
void lbu(int32_t instr_code, int32_t reg_res, int32_t reg_adr, int32_t im) {

    Registors::registors.at(reg_res).value = static_cast<size_t>(RAM::Ram.at(Registors::registors.at(reg_adr).value + im));     
    std::cout << "[lbu] result = " << Registors::registors.at(reg_res).value << '\n';   
}
void lhu(int32_t instr_code, int32_t reg_res, int32_t reg_adr, int32_t im) {

    uint16_t* ptr = reinterpret_cast<uint16_t*>(RAM::Ram.data() + Registors::registors.at(reg_adr).value + im);
    Registors::registors.at(reg_res).value = static_cast<size_t>(*ptr);     
    std::cout << "[lhu] result = " << Registors::registors.at(reg_res).value << '\n';    
}


void sb(int32_t instr_code, int32_t reg_from, int32_t reg_adr, int32_t im) {

    (RAM::Ram.at(Registors::registors.at(reg_adr).value + im)) = static_cast<char>(reg_from);     
    std::cout << "[sb] result = " << RAM::Ram.at(Registors::registors.at(reg_adr).value + im) << '\n';   
}
void sh(int32_t instr_code, int32_t reg_from, int32_t reg_adr, int32_t im) {

    uint16_t* ptr = reinterpret_cast<uint16_t*>(RAM::Ram.data() + Registors::registors.at(reg_adr).value + im);   
    *ptr = static_cast<uint16_t>(Registors::registors.at(reg_from).value);
    std::cout << "[sh] result = " << *ptr << '\n';   
}
void sw(int32_t instr_code, int32_t reg_from, int32_t reg_adr, int32_t im) {

    int32_t* ptr = reinterpret_cast<int32_t*>(RAM::Ram.data() + Registors::registors.at(reg_adr).value + im);
    //Registors::registors.at(reg_from).value = static_cast<int32_t>(*ptr);       
    *ptr = Registors::registors.at(reg_from).value;
    std::cout << "[sw] result = " << *ptr << '\n';   
}


void beq(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) { // надо передавать ссылку на поток

    if (reg_1 == reg_2) {
        // сместить каретку pc;
        std::cout << "jump on " << im << '\n';   
    }
    else 
        std::cout << "don't jump\n";
}
void bne(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) { // надо передавать ссылку на поток

    if (reg_1 != reg_2) {
        // сместить каретку pc;
        std::cout << "jump on " << im << '\n';   
    }
    else 
        std::cout << "don't jump\n";
}
void blt(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) { // надо передавать ссылку на поток

    if (reg_1 < reg_2) {
        // сместить каретку pc;
        std::cout << "jump on " << im << '\n';   
    }
    else 
        std::cout << "don't jump\n";
}
void bge(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) { // надо передавать ссылку на поток

    if (reg_1 >= reg_2) {
        // сместить каретку pc;
        std::cout << "jump on " << im << '\n';   
    }
    else 
        std::cout << "don't jump\n";
}
void bltu(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) { // надо передавать ссылку на поток

    if (static_cast<uint32_t>(reg_1) < static_cast<uint32_t>(reg_2)) {
        // сместить каретку pc;
        std::cout << "jump on " << im << '\n';   
    }
    else 
        std::cout << "don't jump\n";
}
void bgeu(int32_t instr_code, int32_t reg_1, int32_t reg_2, int32_t im) { // надо передавать ссылку на поток

    if (static_cast<uint32_t>(reg_1) >= static_cast<uint32_t>(reg_2)) {
        // сместить каретку pc;
        std::cout << "jump on " << im << '\n';   
    }
    else 
        std::cout << "don't jump\n";
}

};

class Execute {
public:

};
}

#endif