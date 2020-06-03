#include <sys/syscall.h>
#include <stdio.h>
#include <linux/sched.h>

int main(){
	long sysvalue;
	unsigned long info[10];
	int pid = getpid();
	printf("pid: %d\n",pid);
	sysvalue = syscall(546,pid,info);
	int i =0;
	for (i =0;i <10;i++) {
		printf("%lx\n",info[i]);
	}
	for(;;);
}

