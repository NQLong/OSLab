#include "ex1.h"

void getaddress(void *ptr, unsigned int align){
    while ((int)&*ptr % align != 0)
        &*ptr++;
    
}

void* aligned_malloc (unsigned int size , unsigned int align ) {
    void * ptr;
    ptr = sbrk(0);
    printf("%d\n", &*ptr);
    getaddress(ptr,align);
    printf("%d\n", &*ptr);
    while (sbrk(size)==(void*)-1) 
        getaddress(ptr,align);
    ptr = sbrk(0);
    printf("%d\n", &*ptr);
    
    
}

void* aligned_free (void *ptr){
    return;
}

int main() {
    void * ptr = aligned_malloc(30,15);
}
