#include <stdint.h>
#include <sys/types.h>


void function_child(const char *path, char *const argv[]);


void function_debugger(pid_t pid, uint64_t adresse);


void dbugging_exec(const char *path, char *const argv[]);