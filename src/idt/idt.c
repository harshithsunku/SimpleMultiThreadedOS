#include "idt.h"
#include "config.h"
#include "memory.h"
#include "kernel.h"
/**
 * @brief Array of interrupt descriptor structures.
 *
 * This array contains the descriptors for all the interrupts that the CPU
 * can handle. The total number of interrupts is defined by the
 * SIMPLEOS_TOTAL_INTERRUPTS macro in the config.h file.
 */
struct idt_desc idt_descriptors[SIMPLEOS_TOTAL_INTERRUPTS];

/**
 * @brief Structure representing the Interrupt Descriptor Table (IDT) register.
 *
 * This structure is used to hold the base address and the limit of the IDT.
 */
struct idtr_desc idtr_descriptor;

/**
 * @brief Divide by zero interrupt handler.
 *
 * This handler is called when a divide by zero operation is performed.
 * It prints a message to the terminal indicating that a divide by zero error
 * has occurred.
 */
void idt_zero_handler() {
    // Print a message to the terminal indicating that a divide by zero error has occurred.
    print("Divide by zero!\n");
}

/**
 * @brief Sets the IDT entry for a given interrupt number with the provided address.
 *
 * @param interrupt_number The interrupt number to set the IDT entry for.
 * @param address The address of the interrupt handler for the given interrupt number.
 */
void idt_set(int interrupt_number, void *address) {
    // Set the offset_1 field of the IDT descriptor to the lower 16 bits of the address.
    idt_descriptors[interrupt_number].offset_1 = (uint32_t)address & 0xFFFF;
    
    // Set the offset_2 field of the IDT descriptor to the upper 16 bits of the address.
    idt_descriptors[interrupt_number].offset_2 = ((uint32_t)address >> 16) & 0xFFFF;
    
    // Set the selector field of the IDT descriptor to the kernel code selector.
    idt_descriptors[interrupt_number].selector = KERNEL_CODE_SELECTOR;
    
    // Set the type_attr field of the IDT descriptor to 0xEE, indicating an interrupt gate.
    idt_descriptors[interrupt_number].type_attr = 0xEE;
    
    // Set the zero field of the IDT descriptor to 0.
    idt_descriptors[interrupt_number].zero = 0;
}

/**
 * @brief Initializes the Interrupt Descriptor Table (IDT).
 *
 * This function sets up the IDT descriptors, loads the IDT, and configures
 * the IDT. It also sets up the IDT entry for the divide by zero exception.
 *
 * @return void
 */
void idt_init()
{
    // Clear the IDT descriptors
    memset(idt_descriptors, 0, sizeof(idt_descriptors));

    // Set the IDT limit and base address
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base = (uint32_t)idt_descriptors;

    // Set the IDT entry for the divide by zero exception
    idt_set(0x01, idt_zero_handler);

    // Load the IDT
    idt_load(&idtr_descriptor);
}

