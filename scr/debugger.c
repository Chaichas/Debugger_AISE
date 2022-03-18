#include <sys/ptrace.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <syscall.h>
#include <stdint.h>

#include "debugger.h"

//---------------- struct of tracer ----------------


//--------------------------------------------

/*
//Insert trap instruction at the corresponding address + save original data in it
void breakpoint_true(pid_t pid, debug_breakpoint* breakp){

	assert(breakp);
	breakp->data = ptrace(PTRACE_PEEKTEXT, pid, breakp->address, 0);
	ptrace(PTRACE_POKETEXT, pid, breakp->address, (breakp->data & 0xFFFFFF00) | 0xCC);
}

//non-existence of breakpoints
void breakpoint_false(pid_t pid, debug_breakpoint* breakp){

	assert(breakp);
	unsigned data = ptrace(PTRACE_PEEKTEXT, pid, breakp->address, 0);
	assert((data & 0xFF) == 0xCC);
	ptrace(PTRACE_POKETEXT, pid, breakp->address, (data & 0xFFFFFF00) | (breakp->data & 0xFF));
}

//creation of a breakpoint
debug_breakpoint* breakpoint_start(pid_t pid, void* address){

	debug_breakpoint* breakp = malloc(sizeof(*breakp));
	breakp->address = address;
	breakpoint_true(pid, breakp);
    
	return breakp;}

//Cleaning of breakpoints	
void breakpoint_end(debug_breakpoint* breakp){

	free(breakp);
}

//Resuming breakpoints in case of existence of loops
    
int breakpoint_resume(pid_t pid, debug_breakpoint* breakp){

	struct user_regs_struct regs;
	int status_of_wait;
	
	ptrace(PTRACE_GETREGS, pid, 0, &regs); //Read the tracee's registers
	
	regs.rip = (long) breakp->address;
	ptrace(PTRACE_SETREGS, pid, 0, &regs);
	breakpoint_false(pid, breakp);
	
	if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) < 0) {
		perror("ptrace");
		return -1;}
		
		wait(&status_of_wait);
	
		if (WIFEXITED(status_of_wait)) {
			return 0;}
			
	breakpoint_true(pid, breakp);
	
	if (ptrace(PTRACE_CONT, pid, 0, 0) < 0) {
		perror("ptrace");
		return -1;}
		
	wait(&status_of_wait);
	
	if (WIFEXITED(status_of_wait)){
		 return 0;}
	else if (WIFSTOPPED(status_of_wait)) {
		return 1;}
	else{
		return -1;}
} */

//--------------------------------------------

static void handle_signal (int signo)
{
    void *array[500];
    size_t size;

    size = backtrace(array, 500);
    
    fprintf(stderr, "Error: signal %d:\n", signal);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
   //signal (signo, SIG_DFL);
  //psignal (signo, "The signal received : ");
  
}  


void function_child(const char *path, char *const argv[])
{
  ptrace(PTRACE_TRACEME, 0, 0, 0);
  execv(path, argv);
}

void function_debugger(pid_t pid, uint64_t adresse)
{
  
printf(stdout,"debugger started\n");

    wait(0);
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    printf(stdout,"child now at RIP = %p\n", regs.rip);
    debug_breakpoint* bp = breakpoint_start(pid, (void*) adresse);
    printf(stdout,"breakpoint created\n");
    ptrace(PTRACE_CONT, pid, 0, 0);
    wait(0);
 while (1) {
       
        struct user_regs_struct regs;
        ptrace(PTRACE_GETREGS, pid, 0, &regs);
        printf(stdout,"child stopped at breakpoint. EIP = %p\n", regs.rip);
        printf(stdout,"resuming\n");
        
        int rc = breakpoint_resume(pid, bp);

        switch(rc) {
            case 0:
            printf(stdout,"child exited\n");
            break;
        
            case 1:
            continue;
            
            default :
            printf(stdout,"unexpected: %d\n", rc);
            break;
        }
    }

    breakpoint_end(bp);

}



void dbugging_exec(const char *path,const char *path2, char *const argv[])
{
  pid_t child;
  child = fork();
  if (child==0) 
    function_child(path, argv);
  else if (child> 0){
    uint64_t adresse = (uint64_t) strtol(path2, NULL, 16);
    function_debugger(child, adresse);
    }
  else {
    perror("fork");
  }
 
}

int main(int argc, char** argv)
{

for (int i = 0; i < NSIG; i++){
      signal (i, handle_signal);
      psignal (i, "The signal received : ");
}
if (argc < 3) {
        fprintf(stderr, "<program name> --<breakpoint adress> \n");
        return -1;
    }
 dbugging_exec(argv[1],argv[2], argv);

  return 0;
}


