#include <stdio.h>
#include <unistd.h>

struct myMem {
    unsigned int size;
    struct myMem* next;
    int status;
};

#define EXTRA sizeof(struct myMem)

void* Head = NULL;

struct myMem *newMem (unsigned int size, unsigned int align){
    struct myMem* temp;
    void* ptr = sbrk(0);
    printf("%d before break\n",&*ptr);
    
    temp = ptr;
    ptr = sbrk(size+align+sizeof(size_t)+EXTRA);
    printf("%d after break\n",&*ptr);
    if (ptr == (void*)-1) return NULL;
    temp->next=NULL;
    temp->size = size+align;
    temp->status = 1;
    return temp;
}

void* aligned_malloc(unsigned int size, unsigned int align){
    struct myMem* temp;
    if (!Head){
        temp = newMem(size,align);
        printf("%d temp address\n",&*(void*)temp);
        if (!temp) return NULL;
        void *ptr1 = temp+1;
        printf("%d ptr1\n",&*ptr1);
        size_t addr=(size_t)ptr1+align+sizeof(size_t);
        void *ptr2 = (void *)(addr - (addr%align));
        printf("%d ptr2\n",&*ptr1);
        *((size_t *)ptr2-1)=(size_t)ptr1;
        return ptr2;
    }
    else {
        return 0;
    }
}


int main(){
    void *ptr = aligned_malloc(30,5);

    // void *ptr2 = aligned_malloc(30,5);
    // ((struct myMem*)Head)->status =0;
    // void* ptr3 = aligned_malloc(10,6);
}