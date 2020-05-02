#include "ex1.h"

void* aligned_malloc (unsigned int size , unsigned int align ) {
    void * ptr;
    
    ptr = sbrk(0);
    printf("%d\n", &*ptr);
    while (!((int)&*ptr % align == 0 && sbrk(size) != (void*)-1)) {
        &*ptr++;
    }
    printf("%d\n", &*ptr);
    ptr = sbrk(0);
    printf("%d\n", &*ptr);

    
}

void* aligned_free (void *ptr){
    return;
}

int main() {
    void * ptr = aligned_malloc(30,15);
}
