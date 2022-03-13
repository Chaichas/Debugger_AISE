
#include "Breakpoint_process.h"

//Print messages to stdout
void print_process(const char* format, ...)
{
	va_list ap;
	fprintf(stdout, "[%d] ", getpid());
	va_start(ap, format);
	vfprintf(stdout, format, ap);
	va_end(ap);
}
void run_process(const char* programname)
{
    print_process("target started. will run '%s'\n", programname);

    /* Allow tracing of this process */
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
        perror("ptrace");
        return;
    }

    /* Replace this process's image with the given program */
    execl(programname, programname, NULL);
}


long get_child_eip(pid_t pid)
{
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    return regs.rip;
}


void dump_process(pid_t pid, uint64_t from_addr, uint64_t to_addr)
{
    print_process("Dump of %d's memory [%p : %p]\n", pid, from_addr, to_addr);
    for (uint64_t addr = from_addr; addr <= to_addr; ++addr) {
        long word = ptrace(PTRACE_PEEKTEXT, pid, (void*) addr, 0);
        printf("  %p:  %02lx\n", (void*) addr, word & 0xFF);
    }
}


