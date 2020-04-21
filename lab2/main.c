//main.c
#include <stdio.h>
#include "readline.h"
#include "findsubstr.h"
#include <stdlib.h>

#define MAX_LEN 101

/********************************MYGREP***************************************************
**the program will provide you a tool to look up if substr in strings that you provide  **
**the program has 2 mode :                                                              **
**    if the program has 2 or more argument (argc >=3):                                 **
**        we read the last argument as substr                                          **
**        the rest as file's names that we read and look up the substr                  **
**    if the program has argc = 1:                                                      **
**        we read input of strings from users keybord and than substr                   **
**    else:                                                                             **
**        return                                                                        **
*****************************************************************************************/

int main (int argc, char* argv[]){
//Implementmygrep

    //declare variables
    char substr[MAX_LEN];                   //sub string that will be checked whther it is in provided string
    char str[MAX_LEN][MAX_LEN];             //string, will be cheked if it contain substr
    int line=0;                             //count the line of the input string
    int len=0;                              //use as result of read funtion
    int i =0;                               //use for loop 
    int temp=0;                             //use as result of findsubstr function



    //if the arguments passed are smaller than 3
    //get the input string from keyboard and than the sub string
    if (argc < 3)
    {   
        do {
            len = read_line(str[line++]);
        }
        while (len!=-1);
        printf("\n");
        len = read_line(substr);
        if (len==-1) printf("\n");
    }


    //if arguments bigger or equal with 3
    //than we take the last argument as substr 
    //and the rest as file's name
    else if (argc >= 3) {
        
        //get strings from file
        for (i = 1; i < argc-1;i++) {
            FILE* inp;
            inp = fopen(argv[i],"r");
            stdin = inp;
            do {
                len = read_line(str[line++]);
                //printf("%s\n%d\n",str[line-1],len);
            }
            while (len!=-1);
            fclose(inp);
        }

        //get substr
        i=0;
        while (1) {
            substr[i] = argv[argc-1][i];
            if (substr[i]=='\0') 
                break;
            i++;
        }
    }  


    //start checking whether the substr in strings
        for (i = 0; i < line; i++){
            temp = find_sub_string(str[i], substr);
            if (temp!=-1) {
                printf("%s\n", str[i]);
            }   
        }
    

    return 0;
}
