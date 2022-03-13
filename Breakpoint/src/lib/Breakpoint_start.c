#include "Breakpoint_start.h"

static void enable_breakpoint(pid_t pid, debug_breakpoint* bp)
{
    assert(bp);
    bp->orig_data = ptrace(PTRACE_PEEKTEXT, pid, bp->addr, 0);
    ptrace(PTRACE_POKETEXT, pid, bp->addr, (bp->orig_data & ~0xFF) | 0xCC);
}

debug_breakpoint* create_breakpoint(pid_t pid, void* addr)
{
    debug_breakpoint* bp = malloc(sizeof(*bp));
    bp->addr = addr;
    enable_breakpoint(pid, bp);
    return bp;
}
static void disable_breakpoint(pid_t pid, debug_breakpoint* bp)
{
    assert(bp);
    long data = ptrace(PTRACE_PEEKTEXT, pid, bp->addr, 0);
    assert((data & 0xFF) == 0xCC);
    ptrace(PTRACE_POKETEXT, pid, bp->addr, (data & ~0xFF) | (bp->orig_data & 0xFF));
}
