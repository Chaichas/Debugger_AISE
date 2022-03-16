 #ifndef BREAKPOINT_DEBUGGER
 #define BREAKPOINT_DEBUGGER
 
typedef struct debug_breakpoint_type debug_breakpoint;
struct debug_breakpoint_type {
	void* address;
	unsigned Data;
}; 

void breakpoint_true(pid_t pid, debug_breakpoint* breakp);
void breakpoint_false(pid_t pid, debug_breakpoint* breakp);
debug_breakpoint* breakpoint_start(pid_t pid, void* address);
void breakpoint_end(debug_breakpoint* breakp);
int breakpoint_resume(pid_t pid, debug_breakpoint* breakp);

#endif
