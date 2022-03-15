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



//---------------- struct of tracer ----------------

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
    ptrace(PTRACE_GETREGS, child_pid, 0, &regs);
    printf(stdout,"child now at RIP = %p\n", regs.rip);
    debug_breakpoint* bp = create_breakpoint(child_pid, (void*) addr);
    printf(stdout,"breakpoint created\n");
    ptrace(PTRACE_CONT, child_pid, 0, 0);
    wait(0);

    }

    breakpoint_end(bp);

}



void dbugging_exec(const char *path,const char *path2, char *const argv[])
{
  pid_t child;
  child = fork();
  if (child==0) 
    function_child(path, argv);
  else if (child> 0)
    function_debugger(child,uint64_t adresse);
  
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


