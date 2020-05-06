#include <stdio.h>
#include <unistd.h>


struct myMem {//mem block identifier
    unsigned int size;
    struct myMem* next;
    int status;
};

void* Head;
#define EXTRA sizeof(struct myMem)

struct myMem *newMem (unsigned int size, unsigned int align);
struct myMem* findFreeSpace(struct myMem** prev,unsigned int size,unsigned int align);

struct myMem* split(struct myMem** current,unsigned int size,unsigned int align);

void* aligned_malloc(unsigned int size, unsigned int align);

struct myMem* merge(struct myMem** current);
void* aligned_free (void *ptr );

