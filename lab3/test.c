#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    fork();
    printf("%d",getpid());
    while (1) {
        sleep(100);
    }
}