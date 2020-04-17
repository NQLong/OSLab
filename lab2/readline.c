#include "readline.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 101


int read_line(char *str){
    
    int pos = 0;
    char key;
    while (pos < 100) {
        key = fgetc(stdin);
        if (key !=EOF && key != '\n' && key!= '\0')
            str[pos++] =  key;
        else break;
    }
    str[pos] = '\0';
    if (key == EOF)
        return -1;
    
    return pos;

}
