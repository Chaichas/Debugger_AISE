#pragma one
#include <assert.h>

#include <stdint.h>
#include <sys/types.h>


void function_child(const char *path, char *const argv[]);


void function_debugger(pid_t pid, uint64_t adresse);


void dbugging_exec(const char *path,const char *path2, char *const argv[]);

//int backtrace (pid_t pid);

static void handle_signal(int signo);


typedef struct debug_breakpoint{
	void* address;
	unsigned data;
}debug_breakpoint;

void breakpoint_true(pid_t pid, debug_breakpoint* breakp);
void breakpoint_false(pid_t pid, debug_breakpoint* breakp);
debug_breakpoint* breakpoint_start(pid_t pid, void* address);
void breakpoint_end(debug_breakpoint* breakp);
int breakpoint_resume(pid_t pid, debug_breakpoint* breakp);

