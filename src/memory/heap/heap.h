#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stddef.h>

/* Defines for the heap block table entry */
#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01  //!< Block is in use
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00    //!< Block is free

/* Bitmasks for the heap block table entry */
#define HEAP_BLOCK_HAS_NEXT 0b10000000      //!< Block has a next block
#define HEAP_BLOCK_IS_FIRST 0b01000000      //!< Block is the first block

/* Type for the heap block table entry */
typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;  //!< Type for the heap block table entry

/**
 * @brief Structure representing the heap table.
 */
struct heap_table {
    HEAP_BLOCK_TABLE_ENTRY *entries;  //!< Pointer to the heap block table
    size_t total;                    //!< Total number of blocks in the heap
};

/**
 * @brief Structure representing the heap.
 */
struct heap{
    struct heap_table* table;       //!< Pointer to the heap table
    void *saddr;                    //!< Start address of the heap
};

/**
 * @brief Initializes the heap.
 *
 * @param heap Pointer to the heap structure.
 * @param ptr Pointer to the start of the heap.
 * @param end Pointer to the end of the heap.
 * @param table Pointer to the heap table.
 * @return 0 on success, -1 on failure.
 */
int heap_create(struct heap *heap, void *ptr, void *end, struct heap_table *table);

void *heap_malloc(struct heap *heap, size_t size);
void heap_free(struct heap *heap, void *ptr);

#endif

