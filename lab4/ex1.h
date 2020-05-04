#include <stdio.h>
#include <unistd.h>

struct MyMemBlock {
    unsigned int size;
    int status;
    struct MyMemBlock * next;
};

struct MyMemBlock* Head;

void* GetAlignedAddress(void * ptr,int align);

struct MyMemBlock * CheckAvailableBlock (unsigned int size,struct MyMemBlock* cur,struct MyMemBlock* prev);

void* aligned_malloc (unsigned int size , unsigned int align );

struct MyMemBlock * NewMemBlock (unsigned int size,struct MyMemBlock* cur);

struct MyMemBlock * SplitBlock (unsigned int size,struct MyMemBlock* cur);

void * aligned_free (void *ptr );

struct MyMemBlock * SplitBlock (unsigned int size,struct MyMemBlock* prev,MyMemBlock* cur);