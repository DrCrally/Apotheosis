cmake_minimum_required(VERSION 3.10)
project(kernel C ASM)
enable_language(ASM)

# Assume the cross compiler is installed at ~/cross
set(CMAKE_C_COMPILER $ENV{HOME}/cross/bin/i686-elf-gcc)

# Cmake needs to know the language for assembly file
set_property(SOURCE src/boot.s PROPERTY LANGUAGE C)
set_property(SOURCE src/gdt.s PROPERTY LANGUAGE C)
set_property(SOURCE src/idt.s PROPERTY LANGUAGE C)
set_property(SOURCE src/portio.s PROPERTY LANGUAGE C)

# Compiler and linker flags
set(CMAKE_C_FLAGS "-std=c99 -ffreestanding -O2 -msoft-float -mno-sse -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-T ${PROJECT_SOURCE_DIR}/linker.ld -ffreestanding -O2 -nostdlib")

# Set the target and link against libgcc
add_executable(apotheosis.bin src/kernel.c src/vga.c src/text_cursor.c src/gdt.c src/idt.c src/gdt.s src/idt.s src/exception.c src/kcommon.c src/klog.c src/portio.s src/boot.s)
target_link_libraries(apotheosis.bin gcc)
