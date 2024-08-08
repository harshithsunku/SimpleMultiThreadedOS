/**
 * @file memory.h
 * @brief Header file for memory operations.
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h> // Needed for size_t

/**
 * @brief Sets the first size bytes of the block of memory pointed by ptr to the specified value.
 *
 * This function copies the value into the specified memory block.
 *
 * @param ptr Pointer to the memory block to fill.
 * @param c Value to be set.
 * @param size Number of bytes to be set to the value.
 * @return A pointer to the memory block ptr.
 */
void* memset(void* ptr, int c, size_t size);

#endif /* MEMORY_H */
