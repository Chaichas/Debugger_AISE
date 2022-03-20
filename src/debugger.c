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
static void handle_signal(int signum)
{
  signal (signum, SIG_DFL);
  printf("------------------ Signal received --------------\n\n");
  psignal (signum, "The signal received");
  printf("-------------------------------------------------\n\n");
  
} 


//Dispaly pid of child and parent
void display(const char* format, ...)
{
    va_list ap;
    //To dispaly pid of child and parent
    fprintf(stdout, "[%d] ", getpid());
    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);
}


//################### Backtrace function ########################
static void backtrace2(pid_t pid2){
    
    printf("------------------Backtrace startred --------------\n\n");
    
    void *array[600];
    size_t size;

    size = backtrace(array, 5600);

    backtrace_symbols_fd(array, size, STDERR_FILENO);
    printf("-------------------------------------------------\n");
}


//################# Runing child (tracee) ######################
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
  /*
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
  */
    
    int wait_status;
    struct user_regs_struct regs;
    
    display("debugger started\n\n");
    wait(&wait_status);
    
    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    printf("\n");
    printf("-------------------------------------------------\n");
    /* See where the child is now */
    display("child now at RIP = %p\n", regs.rip);
   
    /* Look at the word at the address we're interested in */
    long data = ptrace(PTRACE_PEEKTEXT, pid, (void*)adresse, 0);
    display("Original data at %p: %p\n", adresse, data);
    
    breakpoint_execute(pid,adresse,data,wait_status);
    
    /* See where the child is now */
    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    display("Child stopped at RIP = %p\n", regs.rip);

    breakpoint_false(pid, adresse,data);

    /* The child can continue running now */
    breakpoint_resume(pid,wait_status);
     
    /* Trace function */
    backtrace2(pid);
}


void dbugging_exec(const char *path,const char *path2, char *const argv[])
{
  pid_t child;
  child = fork();
  if (child==0) 
    function_child(path, argv);
  else if (child> 0){
      for (int i = 0; i < NSIG; i++){
      signal (i, handle_signal);
      }
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
