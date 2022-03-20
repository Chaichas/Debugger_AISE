#pragma one
#include <assert.h>

#include <stdint.h>
#include <sys/types.h>
#include "lib/breakpoint_lib.c"


void display(const char* format, ...);

void function_child(const char *path, char *const argv[]);

static void backtrace2(pid_t pid2);

void function_debugger(pid_t pid, uint64_t adresse);


void dbugging_exec(const char *path,const char *path2, char *const argv[]);


static void handle_signal(int signum);
