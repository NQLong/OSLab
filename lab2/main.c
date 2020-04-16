//main.c
#include <stdio.h>
#include "readline.h"
#include "findsubstr.h"
#include <stdlib.h>

#define MAX_LEN 100

int main (int argc, char* argv[]){
//Implementmygrep
    char substr[MAX_LEN];
    char str[MAX_LEN][MAX_LEN];
    int line=0;
    int len=0;
    int i =0;
    int temp=0;
    do {
        len = read_line(str[line++]);
        printf("%s\n", str[line-1]);
    }
    while (len!=-1);
    
    fgets(substr, MAX_LEN, stdin);
    while (1) {
        if (substr[i]=='\n')
            substr[i]='\0';
    } 
    
    for (i = 0; i < len; i++){
        temp = find_sub_string(str[i], substr);
        if (temp!=0) printf("%s\n", str[i]);   
    }
    return 0;
}
