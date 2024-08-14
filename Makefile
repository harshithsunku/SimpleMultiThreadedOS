# This Makefile is used to build the SimpleMultiThreadedOS project.
#
# Targets:
#   all:            Builds the bootloader and kernel binaries.
#   clean:          Cleans the bin and build directories.
#
# Files:
#   - ./bin/boot.bin:     The compiled bootloader binary.
#   - ./bin/kernel.bin:   The compiled kernel binary.
#   - ./bin/os.bin:       The combined bootloader and kernel binary.
#   - ./build/kernel.asm.o:    The compiled kernel assembly object file.
#   - ./build/kernel.o:    The compiled kernel C object file.
#   - ./build/idt/idt.asm.o:    The compiled IDT assembly object file.
#   - ./build/io/io.asm.o:    The compiled IO assembly object file.

# The files to compile.
FILES = ./build/kernel.asm.o ./build/kernel.o ./build/idt/idt.asm.o ./build/idt/idt.o ./build/memory/memory.o ./build/io/io.asm.o

# The include directories for the project.
INCLUDES = -I./src
INCLUDES += -I./src/idt
INCLUDES += -I./src/memory
INCLUDES += -I./src/io

# The compiler flags for the project.
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

# The default target.
all: ./bin/boot.bin ./bin/kernel.bin
	# Combine the bootloader and kernel binaries into a single binary.
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin

# The kernel binary target.
./bin/kernel.bin : $(FILES)
	# Link the kernel object files into a single binary.
	i686-elf-ld -g -relocatable $(FILES) -o  ./build/kernelfull.o
	# Compile the kernel binary.
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -ffreestanding -O0 -nostdlib ./build/kernelfull.o -o ./bin/kernel.bin

# The bootloader binary target.
./bin/boot.bin: ./src/boot/boot.asm
	# Compile the bootloader assembly file into a binary.
	nasm -f bin -g ./src/boot/boot.asm -o ./bin/boot.bin

# The kernel assembly object file target.
./build/kernel.asm.o: ./src/kernel.asm
	# Compile the kernel assembly file into an object file.
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o

# The kernel C object file target.
./build/kernel.o: ./src/kernel.c
	# Compile the kernel C file into an object file.
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o

# The IDT assembly object file target.
./build/idt/idt.asm.o: ./src/idt/idt.asm
	# Compile the IDT assembly file into an object file.
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o

# The IDT C object file target.
./build/idt/idt.o: ./src/idt/idt.c
	# Compile the IDT C file into an object file.
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/idt/idt.c -o ./build/idt/idt.o

# The memory C object file target.
./build/memory/memory.o: ./src/memory/memory.c
	# Compile the memory C file into an object file.
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/memory.c -o ./build/memory/memory.o

# The IO assembly object file target.
./build/io/io.asm.o: ./src/io/io.asm
	# Compile the IO assembly file into an object file.
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o

# The clean target.
clean:
	# Clean the bin and build directories.
	rm -rf ./bin/*	
	rm -rf ./build/*

