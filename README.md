# Debugger_AISE

The debugger implemented in this project consists of the following:
 
	* "debugger.c" and "debugger.h", which include the debugger functions,

	* "breakpoint_lib.c" and "breakpoint_lib.h" in the "lib" folder, which includes the creation of the breakpoint, cleaning of it and resuming of the breakpoints in the case of a loop inside the tested program,

	* A program analyzing function, which includes the source codes "displayNameFunction.c", "envp.c" and "showLibary.c". They are responsible for:

		- "displayNameFunction.c": enables the user to display the function names defined in a c program,

		- "envp.c": enables the user to display the environment variables

		- "showLibary.c": enables the user to list the shared libraries in the program executed using the C code on Linux.
		
		
		
To test the debugger, two test programs have been chosen, which are:

	* "prog_NoLoop.c" program which has no loop inside it,
	* "prog_loop.c" program which has a loop inside it.
	
	
The project is build using a Makefile.
