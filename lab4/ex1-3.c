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
    printf("%d after break\n",sbrk(0));
    if (ptr == (void*)-1) return NULL;
    temp->next=NULL;
    temp->size = size+align;
    temp->status = 1;
    return temp;
}

struct myMem* findFreeSpace(struct myMem** prev,unsigned int size,unsigned int align){
    struct myMem* cur;
    cur = Head;
    while (cur && !(cur->size>=size+align && cur->status==0)){
        *prev = cur;
        cur = cur ->next;
    }
    return cur;
}

void* aligned_malloc(unsigned int size, unsigned int align){
    struct myMem* temp;
    if (!Head){
        temp = newMem(size,align);
        if (!temp) return NULL;
    }
    else {
        struct myMem* prev = Head;
        temp = findFreeSpace(&prev,size,align);
        if (!temp) {
            prev->next = newMem(size,align);
            if (!prev->next) return NULL;
            temp = prev->next;
        }
        else {
            if (temp->size > size+ align +EXTRA + sizeof(size_t)){
                return NULL;
            }
            else {
                temp->status = 1;
            }
        }
    }
    printf("%d temp address\n",&*(void*)temp);
    void *ptr1 = temp+1;
    printf("%d ptr1\n",&*ptr1);
    size_t addr=(size_t)ptr1+align+sizeof(size_t);
    void *ptr2 = (void *)(addr - (addr%align));
    printf("%d ptr2\n",&*ptr2);
    *((size_t *)ptr2-1)=(size_t)ptr1;
    return ptr2;
}


int main(){
    void *ptr1 = aligned_malloc(30,5);
    printf("%d ptr1 address\n",&*ptr1);
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    void *ptr2 = aligned_malloc(30,5);
    printf("%d ptr2 address\n",&*ptr2);
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    ((struct myMem*)Head)->status =0;
    void *ptr3 = aligned_malloc(30,5);
    printf("%d ptr3 address\n",&*ptr3);
    // void *ptr2 = aligned_malloc(30,5);
    // ((struct myMem*)Head)->status =0;
    // void* ptr3 = aligned_malloc(10,6);
}