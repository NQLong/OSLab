#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int usr_interrupt;

int handler(int seg);

void check(pid_t pidnum);

