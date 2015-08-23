/*
Program to create my own shell . The shell should run all the basic shell 
commands. To exit the shell type in command 'exit'
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	int i,j,k;
	while(1)
	{
	
		printf("ARKA'S SHELL >>>> ");
		char *arglist[10];
	
		j=0;
		k=0;
		for(i=0;i<10;i++)
		arglist[i]=(char *)malloc(10*sizeof(char));
		while(1)
		{
			char ch=getchar();
			if(ch==' ')
			{
				arglist[j][k]='\0';
				k=0;
				j++;
			}
			else if(ch=='\n')
			{
				arglist[j][k]='\0';
				break;
			}
			else
			{
				arglist[j][k]=ch;
				k++;
			}
		}

		arglist[j+1]=NULL;
		if(!strcmp(arglist[0],"exit"))
		break;
		
		
		if(!fork())
		{
			//child
			execvp(arglist[0],arglist);
			printf("Bad command or file name\n");
			exit(0);
		}
		//parent
		wait(NULL);
	}
	printf("Exiting ARKA'S SHELL\n");
	return 0;
}

			
