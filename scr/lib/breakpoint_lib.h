 #ifndef BREAKPOINT_DEBUGGER
 #define BREAKPOINT_DEBUGGER
 
typedef struct debug_breakpoint_type debug_breakpoint;
struct debug_breakpoint_type {
	void* address;
	unsigned Data;
}; 

void breakpoint_true(pid_t pid, debug_breakpoint* breakp);

#endif
