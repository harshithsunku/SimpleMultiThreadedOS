#ifndef IDT_H
#define IDT_H

#include <stdint.h>


/**
 * @brief Structure representing an interrupt descriptor.
 *
 * This structure is used to describe an interrupt gate in the Interrupt
 * Descriptor Table (IDT).
 */
struct idt_desc
{
    //! The lower 16 bits of the offset in the code segment to the handler.
    uint16_t offset_1;

    //! The segment selector that specifies the code segment.
    uint16_t selector;

    //! This field must always be zero.
    uint8_t zero;

    /**
     * @brief The type and attributes field.
     *
     * The format of this field is:
     *
     * <pre>
     *  7 | 6 | 5 | 4 | 3 | 2 | 1 | 0
     *   --------------------------
     *   P | DPL| S |  TYPE     |
     * </pre>
     *
     * - P: Present bit. Must be 1 for valid selectors.
     * - DPL: Descriptor Privilege Level.
     * - S: Storage segment flag.
     * - TYPE: Interrupt Gate, Trap Gate, or Task Gate.
     */
    uint8_t type_attr;

    //! The upper 16 bits of the offset in the code segment to the handler.
    uint16_t offset_2;
} __attribute__((packed));


/**
 * @brief Structure representing the Interrupt Descriptor Table (IDT) register.
 *
 * This structure is used to hold the base address and the limit of the IDT.
 */
struct idtr_desc 
{
    /**
     * @brief The size of the IDT in bytes minus 1.
     *
     * The size of the IDT is calculated by taking the total number of bytes
     * occupied by all the IDT entries and subtracting 1.
     */
    uint16_t limit;

    /**
     * @brief The base address of the IDT.
     *
     * The base address of the IDT is the starting address of the IDT in memory.
     */
    uint32_t base;
} __attribute__((packed));


/**
 * @brief Initializes the Interrupt Descriptor Table (IDT).
 *
 * This function sets up the IDT descriptors, loads the IDT, and configures
 * the IDT. It is typically called during the initialization of the system.
 *
 * @return void
 */
void idt_init(void);

extern void idt_load(struct idtr_desc* ptr);

#endif