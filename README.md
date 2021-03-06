# Debugger_AISE Project

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
	
	
The project is build using a Makefile. The different commands are described hereunder.

To display the shared objects (shared libraries) using a C code in the executed program:

	make Run_show_Object
	
To display the shared libraries using the SHELL in the executed program:

	make Run_show_Lib
	
To display the environment variables for a C program:

	make Var_Environment
	
To display the function names defined in a c program:

	make Display_Function_Name
	make Run_Display_Function_Name
	
To run the program analyzer, containing shared libraries, environment variables as well as function names for a given C program:

	make Run_Prog_Analyzer
	
The c test program defined here is "prog_loop.c". However, it is possible to change it in the makefile.

To test the C program output:

	make test_program
	./test_program
	
To execute the breakpoint library defined in the "lib" folder":

	make debugger_library.a
	
To run the debugger using an entry point address:

	make test_program
	readelf -h prog_loop
	./debbuger_bp test_program (Entry point address)
	
To clean everything:

	make clean
	
To make all:

	make all
	
To test the arguments in the main function (in debugger.c):

	make check
	./test_main
