/*********************************************************************************************/
/* This code enables the user to list the loaded objects when running a C program in Linux   */
/* It shows the path of the loaded objects and the ELF Header addresses seg of object files  */
/*********************************************************************************************/
#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>

//DL: Dynamic library
int print(struct dl_phdr_info *info, size_t size, void *data) {
	printf("%s (%d total segment number)\n", info->dlpi_name, info->dlpi_phnum);
	printf("\n");
	printf("Addresses of the ELF Header Segments of object files: \n");
	printf("\n");
	for (int i = 0; i < info->dlpi_phnum; i++){
		printf("\t%2d: %10p\n", i, (void *) (info->dlpi_addr + info->dlpi_phdr[i].p_vaddr));
	
	}
	return 0;
}


int main(int argc, char *argv[]) {
	printf("\n");
	printf("************************************************************************* \n");
	printf("\n");
	printf("#######################     Program Analyzer:     ####################### \n");
	printf("\n");
	printf("************************************************************************* \n");
	printf("\n");
	printf("***********************   Loaded Shared Objects:  *********************** \n");
	printf("\n");
	dl_iterate_phdr(print, NULL); //dl_iterate_phdr - walk through list of shared objects 
	printf("\n");
	printf("************************************************************************* \n");
	printf("\n");
	return 0;
}
