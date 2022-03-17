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

* To display the shared libraries in the executed program:
	make show_library
	make Run_show_library
	
* To display the environment variables:
	make Var_Environment
	
* To display the function names defined in a c program:
	make Display_Function_Name
	make Run_Display_Function_Name
The c test program defined here is "prog_loop.c". However, it is possible to change it in the makefile.

* To test the C program output:
	make test_program
	
* To execute the breakpoint library defined in the "lib" folder"
	make debugger_library.i
	
* To run the debugger:
	make test_program
	make debbuger_bp
	
* To run the debugger which the breakpoint created on a defined address:
	make test_program
	readelf -h prog_loop
	make Run_Breakpoint
	
* To clean everything:
	make clean
	
* To make everything:
	make all
