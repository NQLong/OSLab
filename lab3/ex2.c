#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "ex2.h"

int usr_interrupt=0;

int main(){
    //create new action when recieve SIGURS1 signal
    struct sigaction usr_action;
    sigset_t block_mask;
    pid_t child_id;
    /* Establish the signal handler. */
    sigfillset (&block_mask);
    usr_action.sa_handler = handler;            //trigger handler "handler" when recieve signal
    usr_action.sa_mask = block_mask;
    usr_action.sa_flags = 0;
    sigaction (SIGUSR1, &usr_action, NULL);
    pid_t father =getpid();
    pid_t child[7];
    /////////////////////////////////////////


    //at process A

    child[0] = fork();   //create process B
    check(child[0]);

    if (child[0]>0) {
        //at process A
                 
        child[1] = fork();  //create C
        check(child[1]);
        if (child[1]>0) {
            //still at process A
            child[2] = fork();  //create D
            check(child[2]);
            if (child[2]>0){
                //still at process A
                kill(child[0],SIGUSR1);         //inform process B that it ready to create new proces
                while(!usr_interrupt);          //wait for process B finish creating it children (when B done creating children it send signal(SIGUSR1) and usr_interrupt set to 1)
                kill(child[1],SIGUSR1);         //inform process C that it ready to create new proces
            }
        }
        else if (child[1]==0){  
            while (!usr_interrupt);             //wait for ready signal from father        
            child[5]=fork();                    //create process G
            check(child[5]);
            if (child[5] == 0) {
                //at for cess
                child[6]= fork();               //from process G create process I
                check(child[6]);
            }
        }   
    }
    else if (child[0]== 0) {
        //at process B
        while(!usr_interrupt)                   //waiting for ready signal
            ;
        child[3] = fork();                      //create process E
        check(child[3]);
        if (child[3]> 0) {
            child[4] = fork();                  //create process F
            check(child[4]);
            if (child[4]>0)
                kill(father,SIGUSR1);
        }

    }
   
    if (child[0]==0){
        wait(NULL);
        wait(NULL);
    }
    else if (child[1]==0) wait(NULL);
    else if (child[5]==0) wait(NULL);
    else if (getpid() == father) {
        wait(NULL);
        wait(NULL);
        wait(NULL);
    }

    return 0;
}

int handler(int seg){
    usr_interrupt=1;
    
}

void check(pid_t pidnum){
    if (pidnum<0){
        perror("fork");
        fflush(stderr);
        exit(1);
    }
}
