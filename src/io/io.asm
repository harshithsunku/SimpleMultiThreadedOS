section .asm

; Global functions
global insb ; Read a byte from the specified port
global insw ; Read a word from the specified port
global outb ; Write a byte to the specified port
global outw ; Write a word to the specified port

; Function to read a byte from the specified port
; Parameters:
;   port: The port to read from
; Returns:
;   The byte read from the port
insb:
    push ebp ; Save the base pointer
    mov ebp, esp ; Set the base pointer to the stack pointer

    xor eax, eax ; Clear the EAX register
    mov edx, [ebp+8] ; Move the port value to EDX
    in al, dx ; Read a byte from the specified port into AL

    pop ebp ; Restore the base pointer
    ret ; Return from the function

; Function to read a word from the specified port
; Parameters:
;   port: The port to read from
; Returns:
;   The word read from the port
insw:
    push ebp ; Save the base pointer
    mov ebp, esp ; Set the base pointer to the stack pointer

    xor eax, eax ; Clear the EAX register
    mov edx, [ebp+8] ; Move the port value to EDX
    in ax, dx ; Read a word from the specified port into AX

    pop ebp ; Restore the base pointer
    ret ; Return from the function

; Function to write a byte to the specified port
; Parameters:
;   port: The port to write to
;   value: The byte to write
outb:
    push ebp ; Save the base pointer
    mov ebp, esp ; Set the base pointer to the stack pointer

    mov eax, [ebp+12] ; Move the value to EAX
    mov edx, [ebp+8] ; Move the port value to EDX
    out dx, al ; Write the byte from AL to the specified port

    pop ebp ; Restore the base pointer
    ret ; Return from the function

; Function to write a word to the specified port
; Parameters:
;   port: The port to write to
;   value: The word to write
outw:
    push ebp ; Save the base pointer
    mov ebp, esp ; Set the base pointer to the stack pointer

    mov eax, [ebp+12] ; Move the value to EAX
    mov edx, [ebp+8] ; Move the port value to EDX
    out dx, ax ; Write the word from AX to the specified port

    pop ebp ; Restore the base pointer
    ret ; Return from the function
