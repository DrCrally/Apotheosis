cmake_minimum_required(VERSION 3.10)
project(kernel C ASM)
enable_language(ASM)

set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/cross/bin/i686-elf-gcc)

set_property(SOURCE src/boot.s PROPERTY LANGUAGE C)

set(CMAKE_C_FLAGS "-std=c99 -ffreestanding -O2 -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-T ${PROJECT_SOURCE_DIR}/linker.ld -ffreestanding -O2 -nostdlib -lgcc")

add_executable(apotheosis.bin src/kernel.c src/klib.c src/vga.c src/text_cursor.c src/boot.s)
