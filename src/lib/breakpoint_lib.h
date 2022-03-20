#ifndef BREAKPOINT_DEBUGGER
#define BREAKPOINT_DEBUGGER

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

typedef struct debug_breakpoint{
	void* addr;
	long data;
} debug_breakpoint;

struct user_regs_struct regs;

static void breakpoint_false(pid_t pid, uint64_t adresse, long data);
void breakpoint_execute(pid_t pid, uint64_t adresse, long data,int  _wait);
void breakpoint_resume(pid_t pid,int _wait);

#endif
