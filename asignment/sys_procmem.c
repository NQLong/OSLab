#include <linux/linkage.h>
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
void sys_procmem( int pid, struct proc_segs* info) {
    struct task
}