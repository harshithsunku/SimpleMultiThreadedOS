#ifndef __KHEAP_H__
#define __KHEAP_H__

#include <stdint.h>
#include <stddef.h>

void* kmalloc(size_t size);
void kfree(void* ptr);
void kheap_init();

#endif