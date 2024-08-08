#ifndef KERNEL_H
#define KERNEL_H

/**
 * @brief The width of the VGA console.
 *
 * The VGA console is a character-based display, and this constant defines
 * the number of characters that can be displayed in a single row.
 */
#define VGA_WIDTH 80

/**
 * @brief The height of the VGA console.
 *
 * The VGA console is a character-based display, and this constant defines
 * the number of characters that can be displayed in a single column.
 */
#define VGA_HEIGHT 25

/**
 * @brief Initializes the kernel and prints a greeting message.
 *
 * This function is the entry point of the kernel. It initializes the terminal,
 * prints a greeting message, and sets up the IDT (Interrupt Descriptor Table).
 *
 * @return void
 */
void kernel_main();

/**
 * @brief Prints the given string to the terminal.
 *
 * This function writes the given string to the terminal, character by
 * character, using the terminal_writechar() function.
 *
 * @param str Pointer to the string to be printed.
 *
 * @return void
 */
void print(const char* str);

#endif
