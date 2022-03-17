#To change the permission: chmod +x build.sh
#To run: ./build.sh

#View charged libraries: Using the objdump and grep Commands
#Reference: https://www.baeldung.com/linux/show-shared-libraries-executables

#objdump: displayes information from object files. It is combined with grep to list the required shared libraries of a program.
objdump -p prog_loop | grep 'NEEDED'


#Display the values of environment variables
#Reference: https://www.cyberciti.biz/faq/linux-list-all-environment-variables-env-command/
printenv


#Display all available functions
#Reference: https://stackoverflow.com/questions/4471364/how-do-i-list-the-functions-defined-in-my-shell
set | grep " ()"


#chrt:  contrôle de processus avancés qui permet de déterminer et d’ajuster les attributs en temps réel 
#Reference: https://www.ionos.fr/digitalguide/serveur/configuration/commandes-linux/?
#chrt -p PID


#To check the Memory Usage Per Process on Linux
#reference: https://linuxhint.com/check_memory_usage_process_linux/

ps -o pid,user,%mem,command ax | sort -b -k3 -r
