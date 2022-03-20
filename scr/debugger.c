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


    int wait_status;
    struct user_regs_struct regs;
    //procmsg("debugger started\n");
    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    printf("\n");
    printf("-------------------------------------------------\n");
    //display("child now at RIP = \n", regs.rip);
   

    /* Wait for child to stop on its first instruction */
    wait(&wait_status);

    /* Obtain and show child's instruction pointer */
    ptrace(PTRACE_GETREGS, pid, 0, &regs);

    /* Look at the word at the address we're interested in */
    long data = ptrace(PTRACE_PEEKTEXT, pid, (void*)adresse, 0);

    breakpoint_start(pid,adresse,data,wait_status);
    
    /* See where the child is now */
    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    //procmsg("Child stopped at EIP = %p\n", regs.rip);

    /* Remove the breakpoint by restoring the previous data
    ** at the target address, and unwind the EIP back by 1 to 
    ** let the CPU execute the original instruction that was 
    ** there.
    */

    breakpoint_false(pid, adresse,data);

    /* The child can continue running now */
    breakpoint_resume(pid,wait_status);


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


if (argc < 3) {
        fprintf(stderr, "<program name> --<breakpoint adress> \n");
        return -1;
    }
 dbugging_exec(argv[1],argv[2], argv);

  return 0;
}
