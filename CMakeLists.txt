cmake_minimum_required(VERSION 3.11)
project("RV32I")

set(CMAKE_CXX_STANDARD 17)

set(asm_srcs
    main.cpp
)

set(proc_srcs
    main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-D NDEBUG -O2 -g -std=c++20")


# add_library(asm_lib STATIC ${asm_srcs})
# target_include_directories(asm_lib PUBLIC /include
#                                           /Assembly/include
#                                           /Processor/include)

add_executable(RISC_Simulator.x main.cpp)
# target_link_libraries(RISC_Simulator.x asm_lib)

target_include_directories(RISC_Simulator.x PRIVATE 
            ${CMAKE_SOURCE_DIR}/Assembly/include
            ${CMAKE_SOURCE_DIR}/Processor/include
)
# add_library(proc_lib STATIC ${proc_srcs})
# # target_include_directories(proc_lib PUBLIC /include
# #                                            /Assembly/include
# #                                            /Processor/include)

# add_executable(proc.x ${proc_srcs})
# target_link_libraries(proc.x proc_lib)

# # target_compile_options(intersection.x PRIVATE ${CMAKE_CXX_FLAGS})
target_compile_options(RISC_Simulator.x PRIVATE ${CMAKE_CXX_FLAGS})

# -DCMAKE_BUILD_TYPE=Release -S . -B build
# cmake --build build
# ./build/intersection.x
#
# cmake .. -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=./../../../../include-what-you-use/build/bin/include-what-you-use
# make
