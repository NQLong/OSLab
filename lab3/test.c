#include <stdio.h>
#include <unistd.h>

int main() {
    int i =fork();
    i=fork();
    i=fork();
    printf("%d",getpid());
    pid_t test = getpid();
    printf("%d\n\n",test);
}