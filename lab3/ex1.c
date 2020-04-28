#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include "ex1.h"
/********************************************************************************************************
*the program read numbers from number.txt or file name argv[1]                                          *
*and store in a array of char(if number too large an int or long variable cant contain it)              *
*than it creates 3 child process, each process have a job that count how many number are divisible      *
*by a given number                                                                                      *
********************************************************************************************************/
int main (int argc, int **argv){
    //prepare variable to contain number form testcase.
    char temp[MAX_LEN];
    int line=0;
    FILE *testcase;
    if (argc == 1) {
        testcase = fopen("number.txt","r");
    }
    else if (argc >1) {
        testcase = fopen(argv[1],"r");
    }

    while (!feof(testcase)) {
        fgets(temp,MAX_LEN,testcase);
        line++;
    }

    const int MAX_LINE = line;
    char str[MAX_LINE][80];                 //use this to store readed number.

    rewind(testcase);
    line =0;
    int len;
    while (!feof(testcase)) {   
        fgets(str[line],MAX_LEN,testcase);
        len = modify(str[line]);
        if (len!=0) line++;
    }

    pid_t child1;
    pid_t child2;
    pid_t child3; 
    
    child1 =fork();
    if (child1!= 0) {
        child2 = fork();
        if (child2!=0)
            child3 = fork();
    }
    //this is what process 1 count numbers that divisible by 2
    if (child1==0) {
        int i =0;
        int count =0;
        for (i=0;i<line;i++) {
            if (divisibleby2(str[i])>0) count+=1;
        }
        
        printf("%d\n",count);
        fflush(stdout);
        
    }
    //this is what process 2 count numbers that divisible by 3
    else if (child2==0) {
        int i =0;
        int count =0;
        for (i=0;i<line;i++) {
            if (divisibleby3(str[i])>0)
            { count++;}
        }
        printf("%d\n",count);
        fflush(stdout);
    }
    //this is what process 3 count numbers that divisible by 5
    else if (child3 == 0) {
        int i =0;
        int count =0;
        for (i=0;i<line;i++) {
            if (divisibleby5(str[i])>0) count++;
        }
        printf("%d\n",count);
        fflush(stdout);
    }

    else {
        wait(NULL);                 //wait for all child terminated
        wait(NULL);
        wait(NULL);
    }
    return 0;
    
}

//////////////////////////needed function////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
int divisibleby2(char *str) {
    int i =0;
    while (str[i]!='\0') i++;
    if (((int)str[i-1]%48)%2==0)
        return 1;
    return 0;
}

int divisibleby3(char * str){
    int sum = 0;
    int i =0;
    while (str[i]!='\0') {
        sum += (int)str[i]%48;
        i++;
    }
    if (sum % 3 == 0)
        return 1;
    return 0;
}

int divisibleby5(char *str) {
    int i =0;
    while (str[i]!='\0') i++;
    int lastdigit = (int)str[i-1]%48;
    if (lastdigit == 0 || lastdigit == 5)
        return 1;
    return 0;
}
/**************************************************************
*modify readed value from file which store in str parameter   *
**************************************************************/
int modify(char *str){
    int pos=0;
    for (pos = 0; pos <100-1;pos++){
        if (str[pos]==EOF ||str[pos]=='\n' || str[pos]=='\0' || (int)str[pos]<0)
            break;
    }
    str[pos]='\0';
    return pos;
}