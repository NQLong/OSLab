#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 500
#define MAX_LEN 80

int divisibleby2(char *str) {
    if (((int)str[strlen(str)-1]%48)%2==0)
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
    int lastdigit = (int)str[strlen(str)-1]%48;
    if (lastdigit == 0 || lastdigit == 5)
        
        return 1;
    return 0;
}
void modify(char *str){
    int pos=0;
    for (pos = 0; pos <100-1;pos++){
        if (str[pos]==EOF ||str[pos]=='\n' || str[pos]=='\0' || (int)str[pos]<0)
            break;
    }
    str[pos]='\0';
    
}



int main (){

    char str[MAX_LINE][MAX_LEN];
    int arr[3]={0,0,0};
    int line=0;

    FILE *testcase;
    testcase = fopen("number.txt","r");
    int len;
    
    while (!feof(testcase)) {
        fgets(str[line],MAX_LEN,testcase);
        modify(str[line++]);
    }

    pid_t child1;
    pid_t child2;
    pid_t child3; 
    sigset_t mask , oldmask ;
    child1 =fork();
    if (child1!= 0) {
        child2 = fork();
        if (child2!=0)
            child3 = fork();
    }

    if (child1==0) {
        int i =0;
        int count=0;
        for (i=0;i<line;i++) {
            if (divisibleby2(str[i])>0) count+=1;
        }

    

        printf("2:%d\n",count);
    }
    else if (child2==0) {
        int i =0;
        int count=0;
        for (i=0;i<line;i++) {
            
            if (divisibleby3(str[i])>0){ count++;}
        }
        signal(SIGURS1,parentdone); 

        sigemptyset(&mask);
        sigaddset(&mask,SIGUSR1);
        while ( !usr_interrupt )
            sigsuspend (&oldmask ) ;
        sigprocmask(SIG_UNBLOCK, &mask , NULL) ;
        printf("3:%d\n",count);

    }
    else if (child3 == 0) {
        int i =0;
        int count = 0;
        for (i=0;i<line;i++) {
            if (divisibleby5(str[i])>0) count++;
        }
        signal(SIGURS1,parentdone); 

        sigemptyset(&mask);
        sigaddset(&mask,SIGUSR1);
        while ( !usr_interrupt )
            sigsuspend (&oldmask ) ;
        sigprocmask(SIG_UNBLOCK, &mask , NULL) ;
        printf("5:%d\n",count);

    }
    else {
       wait(NULL);
       kill(child2 , SIGUSR1) ;
       wait(NULL);
       wait(NULL);
    
    }
    return 0;
    
}