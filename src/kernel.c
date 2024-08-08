#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt.h"

/**
 * Pointer to the video memory.
 */
uint16_t* video_mem = 0;

/**
 * Current row of the terminal.
 */
uint16_t terminal_row = 0;

/**
 * Current column of the terminal.
 */
uint16_t terminal_col = 0;

/**
 * Create a character with the given foreground and background colours.
 *
 * @param c The ASCII character to create.
 * @param colour The colour of the character.
 *
 * @return The created character.
 */
uint16_t terminal_make_char(char c, char colour)
{
    /* Shift the colour to the left by 8 bits and OR it with the character.
     * This effectively creates a 16-bit integer where the top 8 bits are the
     * colour and the bottom 8 bits are the character. */
    return (colour << 8) | c;
}

/**
 * Writes a character to the terminal at the specified coordinates.
 *
 * @param x The x-coordinate of the character.
 * @param y The y-coordinate of the character.
 * @param c The character to write.
 * @param colour The colour of the character.
 *
 * @return void
 *
 * @throws None
 */
void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

/**
 * Writes a character to the terminal at the specified coordinates.
 *
 * @param c The character to write.
 * @param colour The colour of the character.
 *
 * @return void
 *
 * @throws None
 */
void terminal_writechar(char c, char colour)
{
    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }
    
    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}
/**
 * Initializes the terminal by setting the video memory address and clearing the screen.
 *
 * @return void
 */
void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }   
}


/**
 * Calculates the length of a null-terminated string.
 *
 * @param str Pointer to the string.
 *
 * @return The length of the string.
 *
 * @throws None
 */
size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len])
    {
        len++;
    }

    return len;
}

/**
 * Prints the given string to the terminal.
 *
 * @param str Pointer to the string to be printed.
 *
 * @return void
 *
 * @throws None
 */
void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

/**
 * Initializes the terminal and prints a greeting message.
 *
 * @return void
 */
void kernel_main()
{
    terminal_initialize();
    print("Harshith!\nWorking...\n");

    idt_init();
}
