#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t usr_interrupt = 0;

void synch_signal (int sig)
{
  usr_interrupt = 1;
}

int main(){
    pid_t child[7];

    struct sigaction usr_action;
    sigset_t block_mask;
    pid_t child_id;

    /* Establish the signal handler. */
    sigfillset (&block_mask);
    usr_action.sa_handler = synch_signal;
    usr_action.sa_mask = block_mask;
    usr_action.sa_flags = 0;
    sigaction (SIGUSR1, &usr_action, NULL);

    child[0] = fork();
    if (child[0]!=0){
        child[1]=fork();
        if (child[1]!=0) {
            child[2]=fork();
            kill(child[0],SIGUSR1);
        }
        else {
            while (!usr_interrupt)
            ;
            usr_interrupt = 0;
            child[5]=fork();
            if (child[5]==0) child[6]=fork();
        }
    }
    else {
        while (!usr_interrupt)
            ;
        usr_interrupt = 0;
        child[3]=fork();
        if (child[3]>0) 
        child[4]=fork();
            kill(child[1],SIGUSR1);
    }

    for (;;);
}