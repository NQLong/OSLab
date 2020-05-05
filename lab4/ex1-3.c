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
    
    temp = ptr;
    ptr = sbrk(size+align+sizeof(size_t)+EXTRA);
   
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

struct myMem* split(struct myMem** current,unsigned int size,unsigned int align){
   
    struct myMem* cur = *current;
    struct myMem* temp;
    void * ptr = (void*)(cur+1);
    ptr += size + sizeof(size_t) + align;
    temp = ptr;
    temp->size= cur->size - (size +align +EXTRA+sizeof(size_t));
    cur ->size = size + align;
    temp->status = 0;
    temp->next = cur->next;
    cur->next = temp;
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
        if (!temp) {
            
            prev->next = newMem(size,align);
            if (!prev->next) return NULL;
            temp = prev->next;
        }
        else {
           
            if (temp->size > size+ align +EXTRA + sizeof(size_t)){
                
                temp = split(&temp,size,align);
                temp->status=1;
            }
            else {
                
                temp->status = 1;
            }
        }
    }
    void *ptr1 = temp+1;
    size_t addr=(size_t)ptr1+align+sizeof(size_t);
    void *ptr2 = (void *)(addr - (addr%align));
    *((size_t *)ptr2-1)=(size_t)ptr1;
    return ptr2;
}

struct myMem* merge(struct myMem** current){
    struct myMem* cur = *current;
    if (cur->next)
        if (cur->next->status == 0){
            cur->size += EXTRA + sizeof(size_t)+cur->next->size;
            cur->next = cur->next->next;
        }
    return cur;
    
}
void* aligned_free (void *ptr ){
    void * res = (void *)(*((size_t *) ptr-1));
    struct myMem* cur = (struct myMem*)res - 1;
    cur->status=0;
    cur = merge(&cur);
    struct myMem* temp = Head;
    if (cur!=temp){
        while (temp->next!= cur)
            temp = temp->next;
        if (temp->status == 0) merge(&temp);
    }
    return NULL;
}

int main(){
    void *ptr1 = aligned_malloc(70,5);
    printf("%d ptr1 address\n",&*ptr1);
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    void *ptr2 = aligned_malloc(30,5);
    printf("%d ptr2 address\n",&*ptr2);
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    struct myMem* prev = Head;
    ptr1 = aligned_free(ptr1);
    void *ptr3 = aligned_malloc(80,5);
    printf("%d ptr2 address\n",&*ptr3);
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    void *ptr4 = aligned_malloc(15,5);
    printf("%d ptr2 address\n",&*ptr4);
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");

    struct myMem* temp = Head;
    while (temp){
        printf("%d\n",temp->size);
        printf("%d\n",temp->status);
        printf("_____________________________________________________\n");
        printf("_____________________________________________________\n");
        temp = temp->next;
    }
    
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    printf("_____________________________________________________\n");
    ptr2 = aligned_free(ptr2);
    ptr3 = aligned_free(ptr3);
    temp = Head;
    while (temp){
        printf("%d\n",temp->size);
        printf("%d\n",temp->status);
        printf("_____________________________________________________\n");
        printf("_____________________________________________________\n");
        temp = temp->next;
    }

}