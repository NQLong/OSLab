#include "ex1.h"

struct MyMemBlock *Head = NULL;


void* GetAlignedAddress(void * ptr,int align) {
    while ((int)&*ptr%align != 0) {
        &*ptr++;
    }
    return &*ptr;
}

struct MyMemBlock * CheckAvailableBlock (unsigned int size,struct MyMemBlock *cur){
    while (cur && !(cur->size>=size && cur->status == 0)){
        cur = cur -> next;
    }
    return &*cur;
}

struct MyMemBlock * NewMemBlock (unsigned int size,struct MyMemBlock* cur,int align){
    void* ptr = NULL;
    ptr = sbrk(0);
    ptr = GetAlignedAddress(ptr,align);
    brk(ptr);
    ptr =sbrk(size + sizeof(struct MyMemBlock));
    if (ptr != (void*)-1) return NULL;

    cur = (struct MyMemBlock*)ptr;
    cur->size = size;
    printf("hello");
    cur->next = NULL;
    cur->status = 1;
    return cur;
}

void* aligned_malloc (unsigned int size , unsigned int align ){
    struct MyMemBlock* tempCur = Head;
    tempCur = CheckAvailableBlock(size,tempCur);
    if (!tempCur) {
        tempCur = &*Head;
        while (!tempCur){
            tempCur = tempCur -> next;
        }
        tempCur = NewMemBlock(size,tempCur,align);
        printf("%d",Head->status);
        return (void*)(tempCur+1);
    }
    return NULL;
}

int main(){
    void* ptr = aligned_malloc(10,10);

}