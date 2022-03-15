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
address = `objdump -d program | grep function | head -n 1 | awk '{print $1;}'`
 
all: debugger_library.i debbuger_bp program

debugger_library.i: ${SRCDIR}/lib.c ${SRCDIR}/lib.h ${SRCDIR}/breakpoint_lib.c ${SRCDIR}/breakpoint_lib.h
	$(LINKER) $(CFLAGS) -O -c ${SRCDIR}/lib.c ${SRCDIR}/breakpoint_lib.c
	ar rcs debugger_library.i ./lib.o ./breakpoint_lib.o

debbuger_bp: debugger.c debugger_library.i
	$(LINKER) $(CFLAGS) $< -o $@ $(LFLAGS)
	
Run_Breakpoint: debugger test_program
	./debugger test_program 0x$(address)

test_program: program.c
	$(CC) $(CCFLAGS) $^ -o $@
 
.PHONY: clean

clean:
	rm -Rf *~ debugger_library.i debbuger_bp *.i *.g *.o
