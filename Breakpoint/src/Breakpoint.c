#include "lib/Breakpoint_process.h"

#include "Breakpoint.h"

void debugger_breakpoint(pid_t pid)
{
	//Starting of the debugger program
	print_process("*** Debugger Breakpoint *** \n");	
	print_process("Start: \n");
	
	//waiting for child to change its state
	print_process("Waiting for child process to change its state \n");
	wait(0);
	
	//Wait is over and child changed its state: Check its position (pointer)
	// print_process("child now at pointer position = %p \n", get_child_eip(pid));
	
}


int main(int argc, char** argv)
{
	return 0;
}
