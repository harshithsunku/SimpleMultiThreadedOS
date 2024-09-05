[BITS 32]
global _start
; The entry point of the kernel
; This should be the first instruction to be executed
extern kernel_main

; Constants for the code/data segments
CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    ; Set up the segments
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Set up the stack
    mov ebp, 0x00200000
    mov esp, ebp

    ; Enable the A20 line
    ; The A20 line is a special line that allows the processor to access
    ; more than 1MB of memory. It is used by the kernel to map the first
    ; 1MB of memory to the upper 1MB of memory.
    in al, 0x92
    or al, 2
    out 0x92, al

    ; Remap the master PIC
    ; The PIC (Programmable Interrupt Controller) is a chip that is used
    ; to handle interrupts. The master PIC is the one that is used to
    ; handle the interrupts for the CPU.
    ; This is a remap of the master PIC to allow for more interrupts
    ; to be handled.
    mov al, 00010001b
    out 0x20, al ; Tell master PIC

    mov al, 0x20 ; Interrupt 0x20 is where master ISR should start
    out 0x21, al

    mov al, 00000001b
    out 0x21, al
    ; End remap of the master PIC

    ; Enable interrupts
    ; This allows the CPU to handle interrupts.
    sti

    ; Call the kernel
    call kernel_main

    ; Infinite loop
    ; This is used to prevent the CPU from executing random code
    ; after the kernel has finished executing.
    ; It is also used to prevent the CPU from crashing.
    jmp $

    ; Fill the rest of the space with zeros
    ; This is used to fill the rest of the 512 bytes of the boot sector
    ; with zeros.
    times 512-($ - $$) db 0
