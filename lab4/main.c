#include "ex1.h"

int main(){
    printf("first call,create an dynamic array with 4 elements and align 1024 \"ptr\" and set their values to 0,1,2,3\n");
    int* ptr= (int*)aligned_malloc(sizeof(int)*4,1024);
    int i =0;
    for (i =0;i<4;i++){
        ptr[i]=i;
    }
    for (i =0;i<4;i++){
        printf("%d ",ptr[i]);
    }
    printf("\n");
    printf("ptr 1st byte address %zd\n",&*ptr);
    printf("second call,create a new array of char (100 element, 1024 align)\n");
    
    char* ptr2= (char*)aligned_malloc(sizeof(char)*100,1024);
    printf("ptr2 1st byte address %zd\n",&*ptr2);
    printf("releasing ptr...\n");
    aligned_free(ptr);
    if (!ptr) pritnf("released");
    printf("third call, make a void pointer with size of 1bytes and align 1024- it should point to the address which ptr point to before we free it\n");
    void* ptr3 = aligned_malloc(1,1024);
    printf("ptr3 1st byte address %zd\n",&*ptr3);
    return 0;
}