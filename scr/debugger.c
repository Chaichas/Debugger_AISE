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

void display(const char* format, ...)
{
    va_list ap;
    fprintf(stdout, "[%d] ", getpid());
    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);
}


static void backtrace2(pid_t pid2){
    
    printf("------------------Backtrace startred --------------\n\n");
    
    void *array[500];
    size_t size;

    size = backtrace(array, 500);

    backtrace_symbols_fd(array, size, STDERR_FILENO);
    printf("-------------------------------------------------\n");
}


/*
static void handle_signal (int signo)
{
    void *array[500];
    size_t size;

    size = backtrace(array, 500);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    psignal (signo, "The signal received : ");
  
}  
*/

void function_child(const char *path, char *const argv[])
{

  printf("\n");
  printf("-----------------------------------------------------------\n");
  printf("##################### Start Program #######################\n");
  printf("-----------------------------------------------------------\n");
  display("Target started. will run '%s'\n\n", path);
  ptrace(PTRACE_TRACEME, 0, 0, 0);
  execv(path, argv);
}

void function_debugger(pid_t pid, uint64_t adresse)
{
    wait(0);
    siginfo_t info;
    ptrace(PTRACE_GETSIGINFO, pid, 0, &info);
    
    printf("---------------------- Signal send -------------------\n");
    printf("Number of signal is : %d \n", info.si_signo);
    
    switch (info.si_signo) {
    case SIGTRAP:
        printf("the signal sent : SIGTRAP \n");
        break;
        
    case SIGSEGV:
        printf("the signal sent : SIGTRAP \n");
        break;
    case SIGCHLD:
         printf("the signal sent : SIGTRAP \n");
    default:
        printf("Got signal : (%s) \n",strsignal(info.si_signo));
    }
    printf("-------------------------------------------------\n");
    ptrace(PTRACE_CONT, pid, 0, 0);
  
display("debugger started\n\n");
    
    backtrace2(pid);
    wait(0);
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    printf("\n");
    printf("-------------------------------------------------\n");
    display("child now at RIP = 0x%08llX\n", regs.rip);
    debug_breakpoint* breakp = breakpoint_start(pid, (void*) 0x1149);
    display("breakpoint created\n");
    ptrace(PTRACE_CONT, pid, 0, 0);
    wait(0);
    
 while (1) {
       
      
        display("child stopped at breakpoint. RIP = 0x%08llX\n", regs.rip);
        display("resuming\n");
        
        int rc = breakpoint_resume(pid, breakp);

        switch(rc) {
            case 0:
            display("child exited\n");
            break;
        
            case 1:
            continue;
            
            default :
            display("unexpected: %d\n", rc);
            break;
        }
    }

    breakpoint_end(breakp);
    printf("\n");

 
}



void dbugging_exec(const char *path,const char *path2, char *const argv[])
{
  pid_t child;
  child = fork();
  if (child==0) 
    function_child(path, argv);
  else if (child> 0){
    uint64_t adresse = (uint64_t) strtol(path2, NULL, 16);
   // for (int i = 0; i < NSIG; i++){
     // signal (i, handle_signal);
      

    function_debugger(child, adresse);
    }
  else {
    perror("fork");
  }
 
}

int main(int argc, char** argv)
{


if (argc < 3) {
        fprintf(stderr, "<program name> --<breakpoint adress> \n");
        return -1;
    }
 dbugging_exec(argv[1],argv[2], argv);

  return 0;
}
