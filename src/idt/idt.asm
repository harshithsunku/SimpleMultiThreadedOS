section .asm

; External functions
extern int21h_handler ; The handler for interrupt 0x21
extern no_interrupt_handler ; The handler for unhandled interrupts

; Global functions
global int21h ; The interrupt 0x21 handler
global idt_load ; The function to load the IDT
global no_interrupt ; The default interrupt handler
global enable_interrupts  ; The function to enable interrupts
global disable_interrupts  ; The function to disable interrupts

; The function to enable interrupts
enable_interrupts:
    sti
    ret

; The function to disable interrupts
disable_interrupts:
    cli
    ret


; The function to load the IDT
idt_load:
    ; Save the base pointer
    push ebp
    ; Set the base pointer to the stack pointer
    mov ebp, esp
    ; Get the address of the IDT from the stack
    mov ebx, [ebp+8]
    ; Load the IDT
    lidt [ebx]
    ; Restore the base pointer
    pop ebp
    ; Return from the function
    ret

; The interrupt 0x21 handler
int21h:
    ; Disable interrupts
    cli
    ; Save all the registers
    pushad
    ; Call the interrupt 0x21 handler
    call int21h_handler
    ; Restore all the registers
    popad
    ; Enable interrupts
    sti
    ; Return from the interrupt handler
    iret

; The default interrupt handler
no_interrupt:
    ; Disable interrupts
    cli
    ; Save all the registers
    pushad
    ; Call the default interrupt handler
    call no_interrupt_handler
    ; Restore all the registers
    popad
    ; Enable interrupts
    sti
    ; Return from the interrupt handler
    iret
