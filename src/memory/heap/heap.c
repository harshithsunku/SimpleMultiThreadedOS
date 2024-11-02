#include"heap.h"
#include"status.h"
#include"memory.h"
#include"config.h"

int heap_validate_alingment(void *ptr){
    if((unsigned int)ptr % SIMPLEOS_HEAP_BLOCK_SIZE_BYTES != 0){
        return 0;
    }
    return 1;
}

int heap_validate_table(void *ptr, void *end, struct heap_table *table){
    if(!ptr || !end || !table){
        return ERROR_NULL_POINTER;
    }

    if(((unsigned int)end - (unsigned int)ptr) / SIMPLEOS_HEAP_BLOCK_SIZE_BYTES != table->total){
        return ERROR_INVALID_ARGUMENT;
    }

    if((unsigned int)ptr % SIMPLEOS_HEAP_BLOCK_SIZE_BYTES != 0){
        return ERROR_INVALID_ARGUMENT;
    }
    if((unsigned int)end % SIMPLEOS_HEAP_BLOCK_SIZE_BYTES != 0){
        return ERROR_INVALID_ARGUMENT;
    }

end:
    return SUCCESS;
}

int heap_create(struct heap *heap, void *ptr, void *end, struct heap_table *table){
    int res = 0;

    if(!heap || !ptr || !end || !table){
        res = ERROR_NULL_POINTER;
        goto end;
    }

    if(!heap_validate_alingment(ptr) || !heap_validate_alingment(end)){
        res = ERROR_INVALID_ARGUMENT;
        goto end;   
    }

    memset(heap, 0, sizeof(struct heap));
    heap->table = table;
    heap->saddr = ptr;

    res = heap_validate_table(ptr,end,table);

    if(res < 0){
        goto end;
    }

    size_t table_size = table->total * sizeof(HEAP_BLOCK_TABLE_ENTRY);
    memset(table->entries, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);

end:
    return res;
}

int heap_get_alligned_size(size_t size){
    if(size % SIMPLEOS_HEAP_BLOCK_SIZE_BYTES == 0){
        return size;
    }

    size = (size - (size % SIMPLEOS_HEAP_BLOCK_SIZE_BYTES));
    return size + SIMPLEOS_HEAP_BLOCK_SIZE_BYTES;
}

static int heap_get_entry_type(HEAP_BLOCK_TABLE_ENTRY entry)
{
    return entry & 0x0f;
}

/**
 * @brief Find the first block in the heap that is free.
 *
 * This function goes through the heap block table and finds the first block
 * that is free. It returns the index of the first block in the table.
 *
 * @param heap Pointer to the heap structure.
 * @return The index of the first free block in the heap.
 */
int heap_get_start_block(struct heap* heap, uint32_t total_blocks)
{
    struct heap_table* table = heap->table;
    int bc = 0;
    int bs = -1;

    for (size_t i = 0; i < table->total; i++)
    {
        // If the block is not free
        if (heap_get_entry_type(table->entries[i]) != HEAP_BLOCK_TABLE_ENTRY_FREE)
        {
            // Reset the block counter
            bc = 0;
            // Reset the block start
            bs = -1;
            // Continue to the next block
            continue;
        }

        // If this is the first block
        if (bs == -1)
        {
            // Set the block start
            bs = i;
        }
        // Increment the block counter
        bc++;
        // If the block counter is equal to the total blocks
        if (bc == total_blocks)
        {
            // Break out of the loop
            break;
        }
    }

    // If the block start is -1
    if (bs == -1)
    {
        // Return an error
        return ERROR_OUT_OF_MEMORY;
    }
    
    // Return the block start
    return bs;

}

void* heap_block_to_address(struct heap* heap, int block)
{
    return heap->saddr + (block * SIMPLEOS_HEAP_BLOCK_SIZE_BYTES);
}

void heap_mark_blocks_taken(struct heap* heap, int start_block, int total_blocks)
{
    int end_block = (start_block + total_blocks)-1;
    
    HEAP_BLOCK_TABLE_ENTRY entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN | HEAP_BLOCK_IS_FIRST;
    if (total_blocks > 1)
    {
        entry |= HEAP_BLOCK_HAS_NEXT;
    }

    for (int i = start_block; i <= end_block; i++)
    {
        heap->table->entries[i] = entry;
        entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
        if (i != end_block -1)
        {
            entry |= HEAP_BLOCK_HAS_NEXT;
        }
    }
}

void* heap_malloc_blocks(struct heap* heap, uint32_t total_blocks)
{
    void* address = 0;

    int start_block = heap_get_start_block(heap, total_blocks);
    if (start_block < 0)
    {
        goto out;
    }

    address = heap_block_to_address(heap, start_block);

    // Mark the blocks as taken
    heap_mark_blocks_taken(heap, start_block, total_blocks);

out:
    return address;
}

void heap_mark_blocks_free(struct heap* heap, int starting_block)
{
    struct heap_table* table = heap->table;
    for (int i = starting_block; i < (int)table->total; i++)
    {
        HEAP_BLOCK_TABLE_ENTRY entry = table->entries[i];
        table->entries[i] = HEAP_BLOCK_TABLE_ENTRY_FREE;
        if (!(entry & HEAP_BLOCK_HAS_NEXT))
        {
            break;
        }
    }
}

int heap_address_to_block(struct heap* heap, void* address)
{
    return ((int)(address - heap->saddr)) / SIMPLEOS_HEAP_BLOCK_SIZE_BYTES;
}


void* heap_malloc(struct heap *heap, size_t size){

    if(!heap || !size){
        return NULL;
    }

    size_t alligned_size = heap_get_alligned_size(size);

    if(alligned_size > heap->table->total * SIMPLEOS_HEAP_BLOCK_SIZE_BYTES){
        return NULL;
    }

    uint32_t total_blocks = alligned_size / SIMPLEOS_HEAP_BLOCK_SIZE_BYTES;

    return heap_malloc_blocks(heap, total_blocks);

}

void heap_free(struct heap* heap, void* ptr)
{
    heap_mark_blocks_free(heap, heap_address_to_block(heap, ptr));
}