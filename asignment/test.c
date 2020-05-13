#include <stdio.h>
#include <linux/sched.h>
#include <unistd.h>

int main(){
    struct task_truct* temp = current;
    temp = find_task_by_vpid(getpid());
    if (temp!=NULL) {
        struct mm_struct *mmtemp= temp->mm;
        printf("%ld",mmtemp->startcode);
    }
}