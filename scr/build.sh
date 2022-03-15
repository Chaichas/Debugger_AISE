#View charged libraries: Using the objdump and grep Commands
#Reference: https://www.baeldung.com/linux/show-shared-libraries-executables

#objdump: displayes information from object files. It is combined with grep to list the required shared libraries of a program.

objdump -p File | grep 'NEEDED'


#display the values of environment variables
#Reference: https://www.cyberciti.biz/faq/linux-list-all-environment-variables-env-command/
 
printenv
