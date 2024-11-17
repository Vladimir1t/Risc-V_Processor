cmake_minimum_required(VERSION 3.11)
project("RV32I")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(asm_srcs
    # main.cpp
    Assembly/src/asm.cpp
)

set(proc_srcs
    Processor/src/proc.cpp
)

# Настройка режима релиза по умолчанию для всех конфигураций
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(FLAGS_DEBUG_1   "-g")
set(FLAGS_DEBUG_2   "-D NDEBUG")


add_executable(RISC_Asm_Simulator.x  ${asm_srcs})
add_executable(RISC_Proc_Simulator.x ${proc_srcs})


target_include_directories(RISC_Asm_Simulator.x PRIVATE 
            ${CMAKE_SOURCE_DIR}/Assembly/include
          
)
target_include_directories(RISC_Proc_Simulator.x PRIVATE 
            ${CMAKE_SOURCE_DIR}/Processor/include
)


target_compile_options(RISC_Asm_Simulator.x  PRIVATE "$<$<CONFIG:RELEASE>:${CMAKE_CXX_FLAGS_RELEASE}>" ${FLAGS_DEBUG_1} ${FLAGS_DEBUG_2})
target_compile_options(RISC_Proc_Simulator.x PRIVATE "$<$<CONFIG:RELEASE>:${CMAKE_CXX_FLAGS_RELEASE}>" ${FLAGS_DEBUG_1} ${FLAGS_DEBUG_2})


# cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
# cmake --build build
# cmake -DCMAKE_BUILD_TYPE=Release
# ./build/intersection.x
#
# cmake .. -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=./../../../../include-what-you-use/build/bin/include-what-you-use
# make
