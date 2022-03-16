#include <stdio.h>

//Function say_hello, which we will create before a breakpoint in the debugger
void say_hello(){

	printf("Hello and welcome in the CHPS Master M1 !"); }

//Main program
int main(){

        for (int i = 0; i < 3; i++){
        	//loop of the say hello: breakpoint should be put in front of the say_hello function at each itteration of the loop
        	say_hello();}
	return 0;
}
