#include "Breakpoint_start.h"

int resume_from_breakpoint(pid_t pid, debug_breakpoint* bp)
{
    struct user_regs_struct regs;
    int wait_status;

    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    /* Make sure we indeed are stopped at bp */
    assert(regs.rip == (long) bp->addr + 1);

    /* Now disable the breakpoint, rewind EIP back to the original instruction
    ** and single-step the process. This executes the original instruction that
    ** was replaced by the breakpoint.
    */
    regs.rip = (long) bp->addr;
    ptrace(PTRACE_SETREGS, pid, 0, &regs);
    disable_breakpoint(pid, bp);
    if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) < 0) {
        perror("ptrace");
        return -1;
    }
    wait(&wait_status);

    if (WIFEXITED(wait_status)) {
        return 0;
    }

    /* Re-enable the breakpoint and let the process run.
    */
    enable_breakpoint(pid, bp);

    if (ptrace(PTRACE_CONT, pid, 0, 0) < 0) {
        perror("ptrace");
        return -1;
    }
    wait(&wait_status);

    if (WIFEXITED(wait_status))
        return 0;
    else if (WIFSTOPPED(wait_status)) {
        return 1;
    }
    else
        return -1;
}
