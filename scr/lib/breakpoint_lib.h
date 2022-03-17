 #ifndef BREAKPOINT_DEBUGGER
 #define BREAKPOINT_DEBUGGER

#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <link.h>
 
typedef struct debug_breakpoint_type debug_breakpoint;
struct debug_breakpoint_type {
	void* address;
	unsigned data;
}; 

void breakpoint_true(pid_t pid, debug_breakpoint* breakp);
void breakpoint_false(pid_t pid, debug_breakpoint* breakp);
debug_breakpoint* breakpoint_start(pid_t pid, void* address);
void breakpoint_end(debug_breakpoint* breakp);
int breakpoint_resume(pid_t pid, debug_breakpoint* breakp);
int print(struct dl_phdr_info *info, size_t size, void *data);

#endif
