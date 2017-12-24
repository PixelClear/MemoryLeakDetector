//
// Created by paritosh on 24/12/17.
//

#ifndef MEMORYALLOCATOR_MEMORYLEAKDETECTOR_H
#define MEMORYALLOCATOR_MEMORYLEAKDETECTOR_H

#include <stdio.h>
#include <cstring>
#include <stdlib.h>

#define malloc(size) xalloc (size, __FILE__, __LINE__)
#define free(size) xfree (size)


typedef struct memory
{
    size_t size;
    char fileName[512];
    size_t lineNumber;
    void* address;

}MemoryInfo;

typedef struct list
{
    MemoryInfo* data;
    struct list* prev;
    struct list* next;

}MemoryBlockList;

void* xalloc(size_t size, const char* fileName, size_t lineNumber);
void xfree(void *ptr);
void reportMemoryLeak();

#endif //MEMORYALLOCATOR_MEMORYLEAKDETECTOR_H
