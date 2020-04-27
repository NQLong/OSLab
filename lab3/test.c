#include <stdio.h>
#include <unistd.h>

int main() {
    int i =fork();
    i=fork();
    i=fork();
    printf("%d",getpid());
    while (1) {
        sleep(100);
    }
}