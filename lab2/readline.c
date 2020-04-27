#include "readline.h"

#include <stdio.h>


#define MAX_LEN 101

/*****************************************************
**function argument:a char pointer str              **
**  +get input from stdin                           **
**  +run a linear search for EOF or \n or '\0       **
**      if meet than replace with \0                **
**  +if EOF founded then return -1                  **
**  +else return str len                            **
*****************************************************/
int read_line(char *str){
    fgets(str,MAX_LEN,stdin);
    int pos = 0;
    for (pos = 0; pos <MAX_LEN-1;pos++){
        if (str[pos]==EOF ||str[pos]=='\n' || str[pos]=='\0' || (int)str[pos]<0)
            break;
    }
    char temp = str[pos];
    str[pos]='\0';
    if (feof(stdin) || temp == EOF || (int)temp<0 )
        return -1;
    return pos;
}


