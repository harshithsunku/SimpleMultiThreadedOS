#!/bin/bash

# Start GDB and load the symbol file
gdb -ex "add-symbol-file build/kernelfull.o 0x100000"  \
    -ex "target remote | qemu-system-i386 -hda bin/os.bin -S -gdb stdio"
