#include "breakpoint_lib.h"

//long ptrace(enum __ptrace_request request, pid_t pid, void *addr, void *data);

/* Insert the trap instruction at its address and save data in it
Case of breakpoint enabling */
static void breakpoint_true(pid_t pid, debug_breakpoint* var){

	assert(var);

	//Read a word at the address addr in the tracee's memory (var->addr)
	var->data = ptrace(PTRACE_PEEKTEXT, pid, var->addr, NULL);

	//Copy the word data to the address addr in the tracee's memory.
	ptrace(PTRACE_POKETEXT, pid, var->addr, (var->data & ~0xFF) | 0xCC);
}


//In case of breakpoints disabling 
static void breakpoint_false(pid_t pid, debug_breakpoint* var){

	assert(var);
	long data = ptrace(PTRACE_PEEKTEXT, pid, var->addr, NULL);

	assert((data & 0xFF) == 0xCC);
	ptrace(PTRACE_POKETEXT, pid, var->addr, (var->data & 0xFF) | (data & ~0xFF));
}


//creation of a breakpoint at the beginning of a function
debug_breakpoint* breakpoint_start(pid_t pid, void* addr){

	debug_breakpoint* var = malloc(sizeof(*var));

	var->addr = addr;

	breakpoint_true(pid, var); //breakpoint enabled
    
	return var;}


//Cleaning of breakpoints	
void breakpoint_end(debug_breakpoint* var){

	free(var); //free pointer
}


/* Resuming breakpoints in case the breakpoint is in front of a function in the prog
that is part of a loop */    
int breakpoint_resume(pid_t pid, debug_breakpoint* var){

	int status_wait;
	
	ptrace(PTRACE_GETREGS, pid, NULL, &regs); //Read the tracee's registers
	/*
	printf("%ld var add",var->addr);
	printf("%ld var regs.rip",regs.rip); */

	assert(regs.rip == (long) var->addr + 1);
	
	regs.rip = (long) var->addr;

	ptrace(PTRACE_SETREGS, pid, NULL, &regs); //Modify the tracee's registers
	
	breakpoint_false(pid, var); //disable breakpoint
	
	//Tracing of process in mode single step
	if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) < 0) {		
		perror("ptrace"); //error
		exit(1);
	}

	//Check the child wait status
	wait(&status_wait);
	
	//Check the child exit status
	if (WIFEXITED(status_wait)) {
		printf("Child exit status: %d\n", WIFEXITED(status_wait));
		return 0;
	}
			
	//Enabling of the breakpoint, proccess runs
	breakpoint_true(pid, var);
	
	if (ptrace(PTRACE_CONT, pid, NULL, NULL) < 0) {
		perror("ptrace"); //error
		exit(1);
	}
		
	//Child wait status
	wait(&status_wait);

	if (WIFEXITED(status_wait)){
		return 0;
	}
	
	if (!WIFSTOPPED(status_wait)){
		fprintf(stderr, "tracing error\n");
		return -1;
	} else{
		return 1;}
	return -1;
	}
