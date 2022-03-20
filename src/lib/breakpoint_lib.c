#include "breakpoint_lib.h"

//Here, breakpoints are disabled
static void breakpoint_false(pid_t pid, uint64_t adresse, long data){

    ptrace(PTRACE_POKETEXT, pid, (void*)adresse, (void*)data); //Copy the word data to the address adresse in the tracee's memory
    regs.rip -= 1;
    ptrace(PTRACE_SETREGS, pid, 0, &regs); //Modify the tracee's registers
}


//creation of a breakpoint at the beginning of a function
void breakpoint_execute(pid_t pid, uint64_t adresse, long data,int  _wait){

    long data_int3 = (data & ~0xFF) | 0xCC; //write int3 instruction in the address of data
    
    ptrace(PTRACE_POKETEXT, pid, (void*)adresse, (void*)data_int3); //Copy the word data_int3 to the address adresse in the tracee's memory

    //Read pid at address
    long read_data = ptrace(PTRACE_PEEKTEXT, pid, (void*)adresse, 0); //Read a word at the address adresse in the tracee's memory
    
    printf("The data, after int3, is at %ld: %ld\n", adresse, read_data);

    // wait for child to reach the breakpoint
    ptrace(PTRACE_CONT, pid, 0, 0);
    wait(&_wait);
    
    if (WIFSTOPPED(_wait)) {
        printf("Child got a signal");
    }
    else {
        return;
    }
}

//Child continues the execution
void breakpoint_resume(pid_t pid,int  _wait){

    ptrace(PTRACE_CONT, pid, 0, 0);
    wait(& _wait);
    printf("Child exited\n");
    
}
