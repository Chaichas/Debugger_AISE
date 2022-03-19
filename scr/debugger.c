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

static void handle_signal (int signo)
{
    void *array[500];
    size_t size;

    size = backtrace(array, 500);
    
    //fprintf(stderr, "Error: signal %p:\n", signal);
    //backtrace_symbols_fd(array, size, STDERR_FILENO);
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
  
fprintf(stdout,"debugger started\n");

    wait(0);
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    printf(stdout,"child now at RIP = %p\n", regs.rip);
    debug_breakpoint* breakp = breakpoint_start(pid, (void*) adresse);
    fprintf(stdout,"breakpoint created\n");
    ptrace(PTRACE_CONT, pid, 0, 0);
    wait(0);
    
 while (1) {
       
      
        fprintf(stdout,"child stopped at breakpoint. RIP = 0x%08llX\n", regs.rip);
        fprintf(stdout,"resuming\n");
        
        int rc = breakpoint_resume(pid, breakp);

        switch(rc) {
            case 0:
            fprintf(stdout,"child exited\n");
            break;
        
            case 1:
            continue;
            
            default :
            fprintf(stdout,"unexpected: %d\n", rc);
            break;
        }
    }

    breakpoint_end(breakp);

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
      //psignal (i, "The signal received : ");
}
if (argc < 3) {
        fprintf(stderr, "<program name> --<breakpoint adress> \n");
        return -1;
    }
 dbugging_exec(argv[1],argv[2], argv);

  return 0;
}
