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
address = `objdump -d prog_loop | grep say_hello | head -n 1 | awk '{print $1;}'`
 

all:  debbuger_bp  test_program 

#debugger_library.i: ${SRCDIR}/breakpoint_lib.c ${SRCDIR}/breakpoint_lib.h
#	$(LINKER) $(CFLAGS) -O -c ${SRCDIR}/breakpoint_lib.c
#	ar rcs debugger_library.i breakpoint_lib.o

debbuger_bp: debugger.c  
	$(LINKER) $(CFLAGS) $< -o $@ $(LFLAGS)
	
Run_Breakpoint: debbuger_bp test_program
	./debbuger_bp test_program 0x$(address)

test_program: prog_loop.c
	$(CC) $(CCFLAGS) $^ -o $@
 
.PHONY: clean

clean:
	rm -Rf *~  debbuger_bp Run_Breakpoint test_program *.i *.g *.o
