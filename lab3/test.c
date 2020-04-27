#include <stdio.h>
#include <unistd.h>

int main() {
    int i =0;
    pid_t k = fork();
    i++;
    printf ("%d",k);
}