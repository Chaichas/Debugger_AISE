/*********************************************************************************************/
/* This code enables the user to list the shared libraries in the program executed using the */
/* C code on Linux.                                                                          */
/*********************************************************************************************/
#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>


int print(struct dl_phdr_info *info, size_t size, void *data) {
  printf("%s\n", info->dlpi_name);
  return 0;
}


int main() {
  dl_iterate_phdr(print, NULL);
  return 0;
}
