#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void* getaddress(void *ptr, unsigned int align);
void* aligned_malloc (unsigned int size , unsigned int align ) ;

void* aligned_free (void *ptr);
