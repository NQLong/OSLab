#include <stdio.h>
#include <unistd.h>

void *Head = NULL;

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
 
};

#define EXTRA sizeof(struct block_meta)

struct block_meta *find_free_block(struct block_meta **prev, size_t size) {
  struct block_meta *cur = Head;
  
  while (cur && !(cur->free && cur->size >= size)) {
    *prev = cur;
    cur = cur->next;
  }
  return cur;
}

struct block_meta *request_space(struct block_meta* last, size_t size) {
    struct block_meta *block;
    block = sbrk(0);
    void *request = sbrk(size + EXTRA);
    
    if (request == (void*) -1) {
        return NULL; // sbrk failed.
    }

    if (last) { // NULL on first request.
        last->next = block;
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;
    
    return block;
}

void *mymalloc(size_t size) {
  struct block_meta *block;
  // TODO: align size?

  if (size <= 0) {
    return NULL;
  }

  if (!Head) { // First call.
    block = request_space(NULL, size);
    if (!block) {
        return NULL;
    }
    Head = block;
  } else {
    struct block_meta *last = Head;
    block = find_free_block(&last, size);
    if (!block) {
      block = request_space(last, size);
      if (!block) {
        return NULL;
      }
    } else {      
      block->free = 0;
      
    }
  }

  return(block+1);
}

void free(void *ptr) {
  if (!ptr) {
    return;
  }

  // TODO: consider merging blocks once splitting blocks is implemented.
 //struct block_meta* block_ptr = get_block_ptr(ptr);
  
  //block_ptr->free = 1;
}

int main(){
    void * temp = mymalloc(15);
}