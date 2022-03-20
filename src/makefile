#Makefile 

# project name
TARGET = Debugger

LINKER = gcc

# Compiling flags
CFLAGS = -std=gnu99  -O0

# linking flags
#LFLAGS = -L. -ldebug
LFLAGS = -L. 

# Proper directories 
SRCDIR = lib


#Tested program is "program.c" and function in front of which we will be putting the breakpoint is called "function"

#objdump is a command-line program for displaying various information about object files on Unix-like operating systems. [Wikipedia]
ADDR = `objdump -d prog_loop | grep say_hello | head -n 1 | awk '{print $1;}'`
 

all:  test_program Run_Prog_Analyzer debbuger_bp

debugger_library.a: ${SRCDIR}/breakpoint_lib.c ${SRCDIR}/breakpoint_lib.h
	$(LINKER) $(CFLAGS) -O -c ${SRCDIR}/breakpoint_lib.c
	ar rcs debugger_library.a breakpoint_lib.o

debbuger_bp: debugger.c  debugger_library.a
	$(LINKER) $(CFLAGS) $< -g -rdynamic -o $@ $(LFLAGS)
	
Run_Breakpoint: debbuger_bp test_program
	./debbuger_bp test_program 0x$(ADDR)

test_program: prog_loop.c
	$(CC) $(CCFLAGS) $^ -o $@
	
Run_show_Lib: shared_lib.sh
	./shared_lib.sh
	
Run_show_Object: showObject
	./showObject

Run_show_reg: registers.sh
	./registers.sh
	
Display_Function_Name: displayNameFunction.c
	$(LINKER) $(CFLAGS) -c displayNameFunction.c
	
Run_Display_Function_Name: displayNameFunction prog_loop.c
	./displayNameFunction prog_loop.c 
	
Var_Environment: envp
	./envp

Run_Prog_Analyzer: Run_show_Object Run_show_Lib Var_Environment Run_show_reg Run_Display_Function_Name

check: debugger.c test_main.c
	$(LINKER) $(CFLAGS) -g test_main.c -o test_main -lcmocka

.PHONY: clean

clean:
	rm -Rf *~  debbuger_bp Run_Breakpoint test_program Run_show_Object Run_Display_Function_Name showObject displayNameFunction Var_Environment envp Run_show_reg test_main *.a *.g *.o
