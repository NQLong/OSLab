#include "ex1.h"

void* aligned_malloc (unsigned int size , unsigned int align ) {
    void * ptr;
    
    ptr = sbrk(0);
    printf("%d", &*ptr);
    while ((int)&*ptr % align != 0) {
        &*ptr++;
    }
    printf("%d", &*ptr);
}

void* aligned_free (void *ptr){
    return;
}

int main() {
    void * ptr = aligned_malloc(15,15);
}
