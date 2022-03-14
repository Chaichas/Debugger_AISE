#include <sys/ptrace.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>


//---------------- the first struct of tracer ----------------

void function_child(const char *path, char *const argv[])
{
  ptrace(PTRACE_TRACEME, 0, 0, 0);
  execv(path, argv);
}

static void function_debugger(pid_t pid, uint64_t adresse)
{
  //TODO :
  - /* Create breakpoint and run to it*/

  while(1) {
    int status;
    waitpid(pid, &status, 0);

    if (WIFSTOPPED(status)) {
      printf("......\n");
      ptrace(PTRACE_CONT, pid, 0, 0);
    } else if (WIFEXITED(status)) {
      printf("......\n");
      exit(0);
    }
  }
}



void dbugging_exec(const char *path, char *const argv[])
{
  pid_t child;
  child = fork();
  if (child==0) 
    function_child(path, argv);
  else if (child> 0)
    function_debugger(child);
  
  else {
    perror("fork");
  }
 
}

int main(int argc, char** argv)
{

if (argc < 2) {
        fprintf(stderr, "Expected a program name as argument\n");
        return -1;
    }
 dbugging_exec(argv[1], argv);

  return 0;
}


