#include "ex1.h"
/*////////////////////////////////////////////////////
program : ex1
goal: provide 2 func
void* aligned_malloc(unsigned int size, unsigned int align)
for allocate new space of memmory with size and align address
void* aligned_free(void* ptr)
free the allocate memory that ptr point to


idea: 
provide new memmory as a block.
the block consists of an identifier ( struct newmem)
                      some offset bytes(>=size of size_t)
                      and the space that return ptr point to

why we need offset bytes. offset bytes must have at list 8 bytes
    this 8 bytes will store the address right after the the identifier
    this will help for freeing memmory

///////////////////////////////////////////////////*/


void* Head = NULL;


/*////////////////////////////////////////////////////
name : newMem
return type: pointer of struct myMem
argument:   size for size of required new space in Heap
            align for aligning address for new space
////////////////////////////////////////////////////*/
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
/*////////////////////////////////////////////////////
name : newMem
return type: pointer of struct myMem
argument:   size for size of required new space in Heap
            align for aligning address for new space
            prev store address of the block previous of located block

goal: find if there is an allocated mem block and sastify size and align.
        return a Null ptr if not exist
////////////////////////////////////////////////////*/
struct myMem* findFreeSpace(struct myMem** prev,unsigned int size,unsigned int align){
    struct myMem* cur;
    cur = Head;
    while (cur && !(cur->size>=size+align && cur->status==0)){
        *prev = cur;
        cur = cur ->next;
    }
    return cur;
}
/*////////////////////////////////////////////////////
name : splt
return type: pointer of struct myMem
argument:   size for size of required new space in Heap
            align for aligning address for new space
            current store address of the block that need to be splitted

goal: split the cuurrent block to 2. first has size = size +align
////////////////////////////////////////////////////*/
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
/*/////////////////////////////////////////
name aligned_malloc
return type: void *
argument: size : requested size
            align: for memmory alignment
goal: retrun pointer point to address aligned by align
and have size of size
/////////////////////////////////////////*/
void* aligned_malloc(unsigned int size, unsigned int align){
    if (size <= 0) return NULL;
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
/*/////////////////////////////////////////////////////////////////
name merge
argument : address of memblock need to merge
return type : struct myMem *

goal merge the current block with the block next to it if it is free
/////////////////////////////////////////////////////////////////*/
struct myMem* merge(struct myMem** current){
    struct myMem* cur = *current;
    if (cur->next)
        if (cur->next->status == 0){
            cur->size += EXTRA + sizeof(size_t)+cur->next->size;
            cur->next = cur->next->next;
        }
    return cur;
    
}
/*/////////////////////////////////////////////////////////////////
name free
argument : pointer need to be free
return type : void*

goal free the passing pointer
/////////////////////////////////////////////////////////////////*/
void* aligned_free (void *ptr ){
    if (!ptr) return ptr;
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
    ptr = NULL;
    return ptr;
}

