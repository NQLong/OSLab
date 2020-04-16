#include "readline.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 255


int read_line(char *str){
    
    fgets(str, MAX_LEN,stdin);
    int i=0;
    for (i=0;i<MAX_LEN;i++) {
        if (str[i]=='\0') 
            break;
        else if  (str[i]=='\n') {
            str[i]='\0';
            break;
        }
    }
    if (feof(stdin)) return -1;
    return i;

}
