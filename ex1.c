#include "ex1.h"

void* aligned_malloc (unsigned int size , unsigned int align ) {
    void * ptr;
    ptr = sbrk(0);
    printf("%p",&ptr);
    printf("%p",&*ptr);
    printf("%d",&ptr);
    printf("%d",&*ptr);
}

void* aligned_free (void *ptr){
    return;
}

int main() {
    void * ptr = aligned_malloc(15,15);
}
