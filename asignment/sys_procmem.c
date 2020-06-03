#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/kernel.h>

struct proc_segs {
unsigned long mssv;
unsigned long start_code;
unsigned long end_code;
unsigned long start_data;
unsigned long end_data;
unsigned long start_heap;
unsigned long end_heap;
unsigned long start_stack;
};

asmlinkage long sys_procmem( int pid, struct proc_segs * info) {
    struct task_struct *temp;
    temp = find_task_by_vpid(pid);
    if (!temp) return -1;
    info->mssv = 1812917;
    struct mm_struct *pmm;
    pmm = temp->mm;
    info->start_code = pmm->start_code;
    info->start_data = pmm->start_data;
    info->start_heap = pmm->start_brk;
    info->start_stack = pmm->start_stack;
    info->end_code = pmm->end_code;
    info->end_data = pmm->end_data;
    info->end_heap = pmm->brk;
    return 1;
}
