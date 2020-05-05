#include "ex1.h"

int main(){
    printf("first call,create an dynamic array with 4 elements and set their values to 0,1,3,4\n");
    int* ptr= (int*)aligned_malloc(sizeof(int)*4,1024);
    int i =0;
    for (i =0;i<4;i++){
        ptr[i]=i;
    }
    for (i =0;i<4;i++){
        printf("%d ",ptr[i]);
    }
    printf("\n");
    printf("%d\n",&*ptr);
    return 0;
}