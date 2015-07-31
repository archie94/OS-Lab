/* one will add even no.  while other will add 
 odd no. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
 
int main()
{
	int n,pid;
	srand(20);
	int a[20];
	int i;
	for(i=0;i<20;i++)
	a[i]=rand()%30;

	printf("nos are \n");
	for(i=0;i<20;i++)
	printf("%d ",a[i]);
	printf("\n");
	if(fork())
	{
		//parent 

		// will calculate sum of even nos.
		if(!fork())
		{
			// child again  
		int sum=0;
		for(i=0;i<20;i++)
		if(a[i]%2==0)
		{printf("%d ",a[i]);sum+=a[i];}
		printf("\nsecond child with pid = %u\n Sum of even =%d\n",getpid(),sum);
		}
	}
	else
	{
		//must be child
		int sum=0;
		for(i=0;i<20;i++)
		if(a[i]%2)
		{printf("%d ",a[i]);sum+=a[i];}
		printf("\nchild with pid = %u\n Sum of odd =%d\n",getpid(),sum);
	}
	return 0;
}
