#include "ex1.h"

int count = 0;
unsigned long alist[1000][2];
void* getaddress(void *ptr, unsigned int align){
    while ((int)&*ptr % align != 0)
        &*ptr++;
    return ptr;
}

void* aligned_malloc (unsigned int size , unsigned int align ) {
    void * ptr;
    ptr = sbrk(0);
    ptr = getaddress(ptr,align);
    brk(ptr);
    printf("%d\n", &*ptr);
    while (sbrk(size)==(void*)-1){
        ptr = getaddress(ptr,align);
        brk(ptr);
    }
    ptr = sbrk(0);
    printf("%d\n", &*ptr);
    return ptr;
    
}

void* aligned_free (void *ptr){
    return;
}

int main() {
    // int * ptr =(int*) aligned_malloc(1,15);
    // ptr[0]=15;
    // ptr[2]=8;
    // printf("%d",ptr[2]);
    int
}
