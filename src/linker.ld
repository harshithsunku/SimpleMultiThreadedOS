/*
 * Linker script for the SimpleMultiThreadedOS project
 *
 * This script is used to control the layout of the final executable file.
 * It specifies the sections and their properties, such as alignment and
 * placement in memory.
 *
 * The entry point is set to _start, which is the default entry point for
 * bare-metal programs.
 *
 * The output format is set to binary, which means the final file will not
 * have any ELF header or other metadata.
 *
 * The sections are defined as follows:
 * - .text: Contains the code section. It is aligned to a 4096-byte boundary.
 * - .rodata: Contains the read-only data section. It is also aligned to a
 *    4096-byte boundary.
 * - .data: Contains the writable data section. It is aligned to a 4096-byte
 *    boundary.
 * - .bss: Contains the uninitialized data section. It is aligned to a
 *    4096-byte boundary.
 * - .asm: Contains any assembly code sections. It is aligned to a 4096-byte
 *    boundary.
 */

ENTRY(_start)
OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 1M;
    .text : ALIGN(4096)
    {
        *(.text)
    }

    .rodata : ALIGN(4096)
    {
        *(.rodata)
    }

    .data : ALIGN(4096)
    {
        *(.data)
    }

    .bss : ALIGN(4096)
    {
        *(COMMON)
        *(.bss)
    }

    .asm : ALIGN(4096)
    {
        *(.asm)
    }
}
