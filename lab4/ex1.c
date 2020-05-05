#include <stdio.h>
#include <unistd.h>

struct myMem {
    unsigned int size;
    struct myMem* next;
    int status;
};

#define EXTRA sizeof(struct myMem)

void* Head = NULL;

void alignAdress(void **ptr,unsigned int align){
    while (((int)(&**ptr)+EXTRA) %align != 0 )
        &**ptr++;
    return;
}

struct myMem *newMem (unsigned int size, unsigned int align){
    struct myMem* temp;
    void* ptr = sbrk(0);
    alignAdress(&ptr,align);
    brk(ptr);
    temp = ptr;
    ptr = sbrk(size+EXTRA);
    if (ptr == (void*)-1) return NULL;
    temp->next=NULL;
    temp->size = size;
    temp->status = 1;
    return temp;
}

struct myMem* findFreeSpace(struct myMem** prev,unsigned int size,unsigned int align){
    struct myMem* cur;
    cur = Head;
    while (cur && !(cur->size>=size && cur->status==0)){
        *prev = cur;
        cur = cur ->next;
    }
    return cur;
}

void* aligned_malloc(unsigned int size, unsigned int align){
    struct myMem* temp;
    if (!Head) {
        temp = newMem(size,align);
        if (!temp) return NULL;
        Head = temp;
        printf("%d\n",&*temp);
        printf("%d\n",&*(temp+1));
        printf("%d\n",sbrk(0));
        return (temp+1);
    }
    else {
        struct myMem* prev=Head;
        temp = findFreeSpace(&prev,size,align);
        if (!temp) {
            prev->next = newMem(size,align);
            temp=prev->next;
            printf("%d\n",&*temp);
            printf("%d\n",&*(temp+1));
            printf("%d\n",sbrk(0));
            return prev->next+1;
        }
        else {
            if (temp->size == size || temp->size <= size+ EXTRA){
                temp->status=1;
                return (temp+1);
                
            }
        }

    }
    
}

//void * aligned_free (void *ptr );


int main(){
    printf("%d heap begin\n",sbrk(0));
    void* ptr = aligned_malloc(10,10);
    printf("%d pointer address\n",&*ptr);
    void* ptr2 = aligned_malloc(10,10);
    printf("%d pointer address\n",&*ptr);
}

