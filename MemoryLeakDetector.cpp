//
// Created by paritosh on 24/12/17.
//
#include "MemoryLeakDetector.h"

#undef malloc
#undef free

MemoryBlockList * head = NULL;
MemoryBlockList* current = NULL;


void reportMemoryLeak()
{
    MemoryBlockList* node;

    if(head != NULL) //There is memory leak
    {
      for(node = head; node != NULL; node=node->next)
      {
          printf("-----Memory Leak Detected-----\n");
          printf("Address: %x\n", node->data->address);
          printf("Address: %s\n", node->data->fileName);
          printf("Address: %d\n", node->data->lineNumber);
          printf("Address: %d\n", node->data->size);
          printf("------------------------------\n");
      }
    }
}

void addMemoryBlockToList(MemoryInfo* memoryInfo)
{
    MemoryBlockList* node = (MemoryBlockList*) malloc(sizeof(MemoryBlockList));
    if(node != NULL)
    {
        node->data = memoryInfo;
        node->next = NULL;
        node->prev = NULL;
    }


    if(head == NULL)
        head = current = node;
    else
    {
        current->next = node;
        node->prev = current;
        current = node;
    }
}

void removeBlockFromList(void * ptr)
{
   MemoryBlockList* node;
   for(node = head ; node != NULL; node= node->next)
   {
       if(node->data->address == ptr)
       {
           if(node == head && head->next != NULL) //There is not only head node
           {
               node->next->prev = head->prev;
               head = node->next;
               free(node->data);
               free(node);
           }
           else if(node == head && head->next == NULL) //Last node
           {
               free(node);
               free(node->data);
               head = NULL;
           }
           else
           {
              node->prev->next = node->next;
              node->next->prev = node->prev;
              free(node->data);
              free(node);
           }
       }
   }
}

void addMemoryBlock(void* ptr, size_t size, const char* fileName, size_t lineNumber)
{
     MemoryInfo *memoryInfo = (MemoryInfo*) malloc(sizeof(MemoryInfo));
     if(memoryInfo != NULL)
     {
         memoryInfo->size = size;
         memoryInfo->address = ptr;
         strcpy(memoryInfo->fileName, fileName);
         memoryInfo->lineNumber = lineNumber;
     }

    addMemoryBlockToList(memoryInfo);
}

void* xalloc(size_t size, const char* fileName, size_t lineNumber)
{
    void * ptr = malloc(size);
    if(ptr != NULL)
    {
        addMemoryBlock(ptr, size, fileName, lineNumber);
    }

    return ptr;
}

void xfree(void *ptr)
{
    removeBlockFromList(ptr);
    free(ptr);
}
