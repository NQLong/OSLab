#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct mylist {
    unsigned long maddress;
    int status;
    size_t size;
    struct mylist next;
};

void* getaddress(void *ptr, unsigned int align);

void* aligned_malloc (unsigned int size , unsigned int align ) ;

void* aligned_free (void *ptr);
