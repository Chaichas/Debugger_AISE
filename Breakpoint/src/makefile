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


 
all: Breakpoint.g Debug_library.i

Debug_library.i: ${SRCDIR}/Breakpoint_process.c ${SRCDIR}/Breakpoint_process.h ${SRCDIR}/Breakpoint_start.c ${SRCDIR}/Breakpoint_start.h ${SRCDIR}/Breakpoint_resume.c ${SRCDIR}/Breakpoint_resume.h ${SRCDIR}/Breakpoint_end.c ${SRCDIR}/Breakpoint_end.h
	$(LINKER) $(CFLAGS) -O -c ${SRCDIR}/Breakpoint_process.c ${SRCDIR}/Breakpoint_start.c ${SRCDIR}/Breakpoint_resume.c ${SRCDIR}/Breakpoint_end.c
	ar rcs Debug_library.i ./Breakpoint_process.o ./Breakpoint_start.o ./Breakpoint_resume.o ./Breakpoint_end.o


Breakpoint.g: Breakpoint.c
	$(LINKER) $(CFLAGS) -O -c Breakpoint.c

 
.PHONY: clean
clean:
	rm -Rf *~ Debug_library.i Breakpoint.g *.i *.g
