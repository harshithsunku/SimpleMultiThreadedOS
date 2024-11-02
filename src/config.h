#ifndef CONFIG_H
#define CONFIG_H


/**
 * @brief The total number of interrupts supported by the CPU.
 *
 * This constant defines the total number of interrupts that the CPU can
 * handle. It is used to define the size of the Interrupt Descriptor Table
 * (IDT).
 */
#define SIMPLEOS_TOTAL_INTERRUPTS 512

/**
 * @brief The selector for the kernel code segment.
 *
 * This constant defines the selector for the kernel code segment. It is used
 * in the IDT to specify the code segment for kernel interrupt handlers.
 */
#define KERNEL_CODE_SELECTOR 0x08

/**
 * @brief The selector for the kernel data segment.
 *
 * This constant defines the selector for the kernel data segment. It is used
 * in the IDT to specify the data segment for kernel interrupt handlers.
 */
#define KERNEL_DATA_SELECTOR 0x10

/**
 * @brief The size of the heap in bytes.
 *
 * This constant defines the size of the heap in bytes. It is used to allocate
 * memory for the heap.
 */
#define SIMPLEOS_HEAP_SIZE_BYTES 0x6400000

/**
 * @brief The size of the heap block in bytes.
 *
 * This constant defines the size of the heap block in bytes. It is used to
 * allocate memory for the heap blocks.
 */
#define SIMPLEOS_HEAP_BLOCK_SIZE_BYTES 0x1000

/**
 * @brief The base address of the heap.
 *
 * This constant defines the base address of the heap. It is used to calculate
 * the physical address of the heap.
 */
#define SIMPLEOS_HEAP_ADDRESS 0x01000000

/**
 * @brief The base address of the heap table.
 *
 * This constant defines the base address of the heap table. It is used to
 * calculate the physical address of the heap table.
 */
#define SIMPLEOS_HEAP_TABLE_ADDRESS 0x00007E00

#endif

