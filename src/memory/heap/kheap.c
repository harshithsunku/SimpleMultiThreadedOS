#include "kheap.h"
#include "config.h"
#include "kernel.h"
#include "memory.h"
#include "heap.h"

/** Pointer to the kernel heap. */
struct heap kernel_heap;

/** Pointer to the kernel heap table. */
struct heap_table kernel_heap_table;

/** Initialize the kernel heap. */
void kheap_init(void) {
    int total_table_entries = SIMPLEOS_HEAP_SIZE_BYTES / SIMPLEOS_HEAP_BLOCK_SIZE_BYTES;
    kernel_heap_table.total = total_table_entries;
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY *)SIMPLEOS_HEAP_TABLE_ADDRESS;

    void* end = (void*)(SIMPLEOS_HEAP_ADDRESS + SIMPLEOS_HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void *)SIMPLEOS_HEAP_ADDRESS, end, &kernel_heap_table);

    if (res < 0) {
        print("Failed to create kernel heap\n");
    }
}

/** Allocate memory on the kernel heap. */
void* kmalloc(size_t size)
{
    return heap_malloc(&kernel_heap, size);
}

/** Free memory allocated by kmalloc. */
void kfree(void* ptr)
{
    heap_free(&kernel_heap, ptr);
}