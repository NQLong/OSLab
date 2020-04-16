//main.c
#include <stdio.h>
#include "readline.h"
#include "findsubstr.h"
#include <stdlib.h>

#define MAX_LEN 100

int main (int argc, char* argv[]){
//Implementmygrep
    char substr[MAX_LEN];
    char* str=(char *)alloc(sizeof(char));
    
    int x=0,y=0;
    do  { 
        x =read_line(str);
        //x = find_sub_string(str,substr);
        printf("%s\n",str);
        

    }
    while (x!=-1);
}