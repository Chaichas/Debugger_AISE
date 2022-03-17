//Insert trap instruction at the corresponding address + save original data in it
void breakpoint_true(pid_t pid, debug_breakpoint* breakp){

	assert(breakp);
	breakp->data = ptrace(PTRACE_PEEKTEXT, pid, breakp->address, 0);
	ptrace(PTRACE_POKETEXT, pid, breakp->address, (breakp->data & 0xFFFFFF00) | 0xCC);
}

//non-existence of breakpoints
void breakpoint_false(pid_t pid, debug_breakpoint* breakp){

	assert(breakp);
	unsigned data = ptrace(PTRACE_PEEKTEXT, pid, breakp->address, 0);
	assert((data & 0xFF) == 0xCC);
	ptrace(PTRACE_POKETEXT, pid, breakp->address, (data & 0xFFFFFF00) | (breakp->data & 0xFF));
}

//creation of a breakpoint
debug_breakpoint* breakpoint_start(pid_t pid, void* address){

	debug_breakpoint* breakp = malloc(sizeof(*breakp));
	breakp->address = address;
	breakpoint_true(pid, breakp);
    
	return breakp;}

//Cleaning of breakpoints	
void breakpoint_end(debug_breakpoint* breakp){

	free(breakp);
}

//Resuming breakpoints in case of existence of loops
int breakpoint_resume(pid_t pid, debug_breakpoint* breakp){

	struct user_regs_struct regs;
	int status_of_wait;
	
	ptrace(PTRACE_GETREGS, pid, 0, &regs); //Read the tracee's registers
	
	regs.rip = (long) breakp->address;
	ptrace(PTRACE_SETREGS, pid, 0, &regs);
	breakpoint_false(pid, breakp);
	
	if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) < 0) {
		perror("ptrace");
		return -1;}
		
		wait(&status_of_wait);
	
		if (WIFEXITED(status_of_wait)) {
			return 0;}
			
	breakpoint_true(pid, breakp);
	
	if (ptrace(PTRACE_CONT, pid, 0, 0) < 0) {
		perror("ptrace");
		return -1;}
		
	wait(&status_of_wait);
	
	if (WIFEXITED(status_of_wait)){
		 return 0;}
	else if (WIFSTOPPED(status_of_wait)) {
		return 1;}
	else{
		return -1;}
}


int print(struct dl_phdr_info *info, size_t size, void *data) {
	printf("%s\n", info->dlpi_name);
	return 0;
}

int main() {
	dl_iterate_phdr(print, NULL);
	return 0;
}
