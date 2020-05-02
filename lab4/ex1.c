#include "ex1.h"

void* aligned_malloc (unsigned int size , unsigned int align ) {
    void * ptr;
    ptr = sbrk(0);
    printf("%p\n",&ptr);
    printf("%p\n",&*ptr);
    printf("%d\n",&ptr);
    printf("%d\n",&*ptr);
}

void* aligned_free (void *ptr){
    return;
}

int main() {
    void * ptr = aligned_malloc(15,15);
}
