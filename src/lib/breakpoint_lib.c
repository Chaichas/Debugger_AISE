#include "breakpoint_lib.h"




//In case of breakpoints disabling 
static void breakpoint_false(pid_t pid, uint64_t adresse, long data){

    ptrace(PTRACE_POKETEXT, pid, (void*)adresse, (void*)data);
    regs.rip -= 1;
    ptrace(PTRACE_SETREGS, pid, 0, &regs);
}


//creation of a breakpoint at the beginning of a function
void breakpoint_start(pid_t pid, uint64_t adresse, long data,int  _wait){

    /* Write the trap instruction 'int 3' into the address */
    long data_with_trap = (data & ~0xFF) | 0xCC;
    ptrace(PTRACE_POKETEXT, pid, (void*)adresse, (void*)data_with_trap);

    /* See what's there again... */
    long readback_data = ptrace(PTRACE_PEEKTEXT, pid, (void*)adresse, 0);
    display("After trap data at %p: %p\n", adresse, readback_data);

    /* Let the child run to the breakpoint and wait for it to
    ** reach it 
    */
    ptrace(PTRACE_CONT, pid, 0, 0);

    wait(&_wait);
    if (WIFSTOPPED(_wait)) {
        printf("Child got a signal");
    }
    else {
        perror("wait");
        return;
    }
}




/* Resuming breakpoints in case the breakpoint is in front of a function in the prog
that is part of a loop */    
void breakpoint_resume(pid_t pid,int  _wait){

    ptrace(PTRACE_CONT, pid, 0, 0);

    wait(& _wait);

    if (WIFEXITED( _wait)) {
        printf("Child exited\n");
    } 
    else {
        printf("Unexpected signal\n");
    }
}
