#include <iostream>
#include <fstream>
#include <vector>

#include "risc_proc.hpp"

int main(int argc, const char* argv[]) {

    Risc_v::Decoder dec;

    if (argc < 3)
        return 0;
    
    std::ifstream bytecode;
    bytecode.open(argv[1], std::ios::binary);

    std::ofstream result_file;
    result_file.open(argv[2]);

    if (!(bytecode.is_open() && result_file.is_open())) {
        std::cerr << "File wasn't opened\n";
        return 0;
    }

    int instr_code;

    while (bytecode.read(reinterpret_cast<char*>(&instr_code), sizeof(instr_code))) {
        std::cout << "instr_code = " << instr_code << std::endl;

        dec.decode_instr(instr_code);
    }

    for (int i = 0; i != Risc_v::Registors::registors.size(); ++i) {
        std::cout << "reg[" << i << "] = " << Risc_v::Registors::registors.at(i).value << '\n';
    }

    bytecode.close();
    result_file.close();

    return 0;
}