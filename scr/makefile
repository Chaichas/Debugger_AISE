#Makefile 

# project name
TARGET = Debugger

LINKER = gcc

# Compiling flags
CFLAGS = -std=gnu99  -O0

# linking flags
LFLAGS = -L. -ldebug

# Proper directories 
SRCDIR = lib


#Tested program is "program.c" and function in front of which we will be putting the breakpoint is called "function"

#objdump is a command-line program for displaying various information about object files on Unix-like operating systems. [Wikipedia]
address = `objdump -d prog_loop | grep function | head -n 1 | awk '{print $1;}'`
 
all: debugger_library.i debbuger_bp prog_loop show_library

debugger_library.i: ${SRCDIR}/breakpoint_lib.c ${SRCDIR}/breakpoint_lib.h
	$(LINKER) $(CFLAGS) -O -c ${SRCDIR}/breakpoint_lib.c
	ar rcs debugger_library.i ./breakpoint_lib.o

debbuger_bp: debugger.c debugger_library.i
	$(LINKER) $(CFLAGS) $< -o $@ $(LFLAGS)
	
Run_Breakpoint: debugger test_program
	./debugger test_program 0x$(address)

test_program: prog_loop.c
	$(CC) $(CCFLAGS) $^ -o $@

show_library: showLibary.c
	$(LINKER) $(CFLAGS) -c showLibary.c

Run_show_library: showLibary prog_loop.c
	./showLibary prog_loop.c

 
.PHONY: clean

clean:
	rm -Rf *~ debugger_library.i debbuger_bp *.i *.g *.o
