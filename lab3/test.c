#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t i =fork();
    pid_t k =fork();
    pid_t u=fork();
    printf("%d\n",getpid());
    pid_t test = getpid();
    printf("%d %d %d %d\n\n",i,u,k,getppid());
    
}