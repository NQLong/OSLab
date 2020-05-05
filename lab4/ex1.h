#include <stdio.h>
#include <unistd.h>
// #include <sys/types.h>
// #include<stddef.h>

struct MyMemBlock {
    unsigned int size;
    struct MyMemBlock * next;
    int status;
};

struct MyMemBlock* Head;

void* GetAlignedAddress(void * ptr,int align);

struct MyMemBlock * CheckAvailableBlock (unsigned int size,struct MyMemBlock* cur);

void* aligned_malloc (unsigned int size , unsigned int align );

struct MyMemBlock * NewMemBlock (unsigned int size,struct MyMemBlock* cur,int align);

struct MyMemBlock * SplitBlock (unsigned int size,struct MyMemBlock* cur,struct MyMemBlock* prev);

void * aligned_free (void *ptr );
