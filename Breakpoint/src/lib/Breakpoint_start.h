#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h> 
#include "Breakpoint_process.h"

debug_breakpoint* create_breakpoint(pid_t pid, void* addr);
static void enable_breakpoint(pid_t pid, debug_breakpoint* bp);
static void disable_breakpoint(pid_t pid, debug_breakpoint* bp);
