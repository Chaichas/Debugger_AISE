#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <unistd.h>
#include <errno.h>


void print_process(const char* format, ...);
void run_process(const char* programname);
long get_child_eip(pid_t pid);
void dump_process(pid_t pid, uint64_t from_addr, uint64_t to_addr);

struct debug_breakpoint_t {
    void* addr;
    long orig_data;
};
struct debug_breakpoint_t;
typedef struct debug_breakpoint_t debug_breakpoint;