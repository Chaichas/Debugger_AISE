/*********************************************************************************************/
/* This code enables the user to display the function names defined in a c program          */
/*******************************************************************************************/
#include <stdio.h>
#include <string.h>
 
// Print name of function character by character
void display_function_name(char *c,int p1)
{
    int temp = p1, i;
 
    while (c[--temp] != ' ');
    for (i = temp + 1; i < p1; i++){ 
        printf("%c", c[i]);}
	printf("\n");
    return;
 
}

//Check if it is a function
void check_function(char *c, int p1, int p2)
{
    int i, flag = 0, temp = p1;
 
    if ((c[p1 + 1] == ')'))
    {
        display_function_name(c, p1);
        return;
    }
    for (i = p1 + 1; i < p2; i++)
    {
        if ((c[i] != ' ') || (c[i] == ')'))
        {
            flag = 1;
 
        }
        if (flag == 0)
        {
            display_function_name(c, p1);
            return;
        }
        else
        {
            flag = 0;
            while (c[--temp] != ' ');
            for (i = 0; i < temp; i++)
                if (c[i]==' ')
                {
                    flag = 1;
                }
                if (flag == 0)
                {
                    display_function_name(c, p1);
                    return;
                 }
                 else
                     return;
          }
    }
}

//Check the functions in a program 
void function_prog (FILE *fp, char *ch, char *position1, char *position2, char *position3){
while (1)
    {
        if ((fgets(ch, 100, fp)) != NULL) //read char of a file and store it in a tab
        {
            if ((strstr(ch, "/*")) == NULL)
            {
                position1 = strchr(ch, '('); //check if there is opening brace (
                if (position1)
                {
                    position2 = strchr(ch,')'); //chech if there is closing brace)
                    if (position2)
                    {
                        position3 = strchr(ch,';'); //check if there is a semi-colomn;
                        
                        if ((position1 < position2) && (position3 == NULL) || (position3 < position1))
                        {
                            check_function(ch, position1 - ch, position2 - ch);
                        }
                        else    continue;
                    }
                    else    continue;
                }
                else    continue;
            }
            else    continue;
        }
        else    break;
    }
    fclose(fp);
}
 

//Main Program 
void main(int argc, char **argv)
{
    FILE *fp;
    char ch[100];
    char *position1, *position2, *position3;
 
    fp=fopen(argv[1], "r"); //open file
    if (fp == NULL)
    {
        printf("\nFile unable to open");
        return;
    }
    else
        printf("\n");
	printf("*********************** Functions in the Program: *********************** \n");
	function_prog (fp, ch, position1, position2, position3);
	printf("\n");
	printf("************************************************************************* \n");
    
}
