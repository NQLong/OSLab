#include "ex1.h"

struct MyMemBlock *Head = NULL;

void* GetAlignedAddress(void * ptr,int align) {
    while ((int)&*ptr%align != 0) {
        &*ptr++;
    }
    return ptr;
}

struct MyMemBlock * CheckAvailableBlock (unsigned int size,struct MyMemBlock* cur,struct MyMemBlock* prev){
    while (cur && !(cur->size>=size && cur->status == 0)){
        prev = cur;
        cur = cur -> next;
    }
}

void* aligned_malloc (unsigned int size , unsigned int align ){
    Head = sbrk(sizeof(struct MyMemBlock));
    Head->next = sbrk(sizeof(struct MyMemBlock));
    Head->next->status=1;
    Head->status = 0;
    printf("%d\n",Head->status);
    printf("%d\n",Head->next->status);
    struct MyMemBlock* tempCur = Head;
    struct MyMemBlock* tempPrev = tempCur;

    tempCur = CheckAvailableBlock(size,&tempCur,&tempPrev);
    printf("%d\n",tempPrev->status);
    if (!Head) {
        //Head = NewMemBlock(size,Head);
        if (!Head) {
            perror("Something went wrong");
        }
        else return (void*)(-1);
    }
    return NULL;
}

int main(){
    void* ptr = aligned_malloc(10,10);
}