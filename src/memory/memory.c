#include "memory.h"

/**
 * @brief Sets the first size bytes of the block of memory pointed by ptr to the
 * specified value (interpreted as an unsigned char).
 *
 * This function copies the value into the specified memory block.
 *
 * @param ptr Pointer to the memory block to fill.
 * @param c Value to be set.
 * @param size Number of bytes to be set to the value.
 * @return A pointer to the memory block ptr.
 */
void* memset(void* ptr, int c, size_t size)
{
    // Typecast the void pointer into a char pointer
    char* p = (char*)ptr;
    
    // Loop through the specified number of bytes
    for (size_t i = 0; i < size; i++)
    {
        // Set the value at the current index to the specified value
        p[i] = c;
    }
    
    // Return the original pointer
    return ptr;
}
