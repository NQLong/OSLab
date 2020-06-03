#include "procmem.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
long procmem(pid_t pid, struct proc_segs * info) {
    long sysvalue;
    unsigned long info[SIZE];
    sysvalue = syscall([number_32], 1, info);
    if (sysvalue==-1) return -1;
    else return 1;
}