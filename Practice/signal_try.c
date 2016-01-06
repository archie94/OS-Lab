/* Program to Display "Hello" , then "World" and finally exit on third press Ctrl+C in  terminal */



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>


void handler2(int s)
{
	printf("World\n");
	signal(SIGINT,SIG_DFL);
}
void handler1(int s)
{
	printf("Hello\n");
	signal(SIGINT,handler2);
}
int main()
{
	signal(SIGINT, handler1);
	int c = 0;
	while(1)
	{
		printf("Counting %d\n",c++);
		sleep(1);
	}
	return 0;
}

