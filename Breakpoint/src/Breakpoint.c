#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void debugger_breakpoint()
{
	..
}

void debugger_run(pid_t pid)
{
	//Starting of the debugger program
	procmsg("*** Debugger Breakpoint *** \n");	
	procmsg("Start: \n");
	
	//waiting for child to change its state
	procmsg("Waiting for child process to change its state \n");
	wait(0);
	
	//Wait is over and child changed its state: Check its position (pointer)
	procmsg("child now at pointer position = %p \n", get_child_eip(pid));
	
}

int main(int argc, char* argv)
{
	..
}
