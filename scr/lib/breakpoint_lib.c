 #include "breakpoint_lib.h"
 
//Insert trap instruction at the corresponding address + save original data in it
void breakpoint_true(pid_t pid, debug_breakpoint* breakp){

	assert(breakp);
	breakp->Data = ptrace(PTRACE_PEEKTEXT, pid, breakp->address, 0);
	ptrace(PTRACE_POKETEXT, pid, breakp->address, (breakp->Data & 0xFFFFFF00) | 0xCC);
}

void breakpoint_false(pid_t pid, debug_breakpoint* breakp){

	assert(breakp);
	unsigned Data = ptrace(PTRACE_PEEKTEXT, pid, breakp->address, 0);
	assert((data & 0xFF) == 0xCC);
	ptrace(PTRACE_POKETEXT, pid, breakp->address, (Data & 0xFFFFFF00) | (breakp->Data & 0xFF));
}
