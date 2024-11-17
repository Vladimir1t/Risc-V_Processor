#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

#include "risc_asm.hpp"

int main(int argc, const char* argv[]) {

    if (argc < 3)
        return 0;
    
    std::ifstream asm_file;
    asm_file.open(argv[1]);

    std::ofstream bytecode;
    bytecode.open(argv[2], std::ios::binary);

    if (!(asm_file.is_open() && bytecode.is_open())) {
        std::cerr << "File wasn't opened\n";
        return 0;
    }

    std::string str_com;

    while (asm_file >> str_com) {
        std::cout << "command = " << str_com << std::endl;
        for (auto command : Instruction::commands) {
            if (command.name == str_com) {
                #ifndef NDEBUG
                    std::cout << "Find instr\n";
                #endif
                command.func(asm_file, bytecode);
                break;
            }
        }
    }
    int32_t code = 0x2062383; // lw x7, 32(x12)
    bytecode.write(reinterpret_cast<const char*>(&code), sizeof(code));
    code = 0x850283; // lb x5, 8(x10)
    bytecode.write(reinterpret_cast<const char*>(&code), sizeof(code));
    code = 0x46C403; // lbu x8, 4(x13)
    bytecode.write(reinterpret_cast<const char*>(&code), sizeof(code));

    code = 0x2208063;  // beq x1, x2, 16
    bytecode.write(reinterpret_cast<const char*>(&code), sizeof(code));
    code = 0xFE20CAE3; // blt x1, x2, -6
    bytecode.write(reinterpret_cast<const char*>(&code), sizeof(code));
    code = 0x241F263;  // bgeu x3, x4, 20
    bytecode.write(reinterpret_cast<const char*>(&code), sizeof(code));

    asm_file.close();
    bytecode.close();

    return 0;
}