#include "ex1.h"

int main(){
    printf("first call,create an dynamic array with 4 elements and set their values to 0,1,3,4\n");
    int* ptr= (int*)aligned_malloc(sizeof(int)*4,1024);
    for (int i =0;i<4;i++){
        ptr[i]=i;
    }
    for (int i =0;i<4;i++){
        pritnf("%d ",ptr[i]);
    }
    printf("\n");
    pritnf("%d\n",&*ptr);
    return 0;
}