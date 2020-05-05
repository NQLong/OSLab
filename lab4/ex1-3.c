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
    if (!cur) printf("we dead");
    while (cur && !(cur->size>=size+align && cur->status==0)){
        *prev = cur;
        printf("%d\n", cur->status);
        cur = cur ->next;
    }
    return cur;
}

void* aligned_malloc(unsigned int size, unsigned int align){
    struct myMem* temp;
    if (!Head){
        temp = newMem(size,align);
        if (!temp) return NULL;
        Head= temp;
    }
    else {
        struct myMem* prev = Head;
        temp = findFreeSpace(&prev,size,align);
        printf("hello");
        if (!temp) {
            prev->next = newMem(size,align);
            if (!prev->next) return NULL;
            temp = prev->next;
        }
        else {
            printf("hello");
            if (temp->size > size+ align +EXTRA + sizeof(size_t)){
                return NULL;
                 printf("hello");
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
void* aligned_free (void *ptr ){
    void * res = (void *)(*((size_t *) ptr-1));
    struct myMem* temp = (struct myMem*)res - 1;
    printf("%zd real address\n",&*(void*)temp);
    temp->status=0;
    printf("%d\n",temp->status);
    return NULL;
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
    struct myMem* prev = Head;
    ptr1 = aligned_free(ptr1);
    void *ptr3 = aligned_malloc(40,5);
    printf("%d ptr2 address\n",&*ptr3);
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    void *ptr4 = aligned_malloc(30,5);
    printf("%d ptr2 address\n",&*ptr4);
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    // // // struct myMem* temp; 
    // // // temp= Head;
    // // // temp->status = 0;
    // // // printf("hello");
    // void *ptr3 = aligned_malloc(30,5);
    // printf("%d ptr3 address\n",&*ptr3);
    // // void *ptr2 = aligned_malloc(30,5);
    // // ((struct myMem*)Head)->status =0;
    // // void* ptr3 = aligned_malloc(10,6);
}