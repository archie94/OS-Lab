/* Count the maximum number of
processes that can run in
your system */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#define LOOP 10
int main()
{
	int i,pid;
	int counter = 0;
	for(i=0;1;i++)
	{
		pid=fork();
		if(pid<0)
		{
			printf("error\n");
			break;
		}
		else if(pid==0)
		{
			printf("child no =%d child with pid = %u\n",counter+1,getpid());
			exit(1);
		}
		/*else
		{
			printf("parent with pid = %u \n",getpid());
		}*/
		counter++;
		//if(i==(LOOP - 1))
		//printf("NO of successful child creation = %d\n",counter);
	}
	printf("NO of successful child creation = %d\n",counter);
	return 0;
}
