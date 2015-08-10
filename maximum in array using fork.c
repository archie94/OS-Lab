/*
	Write a C program that creates a tree of process in order to recursively find out the maximum number in an array
of integers. The process at the root of tree reads 'n' the total number of integers in array, then an array of size n is 
populated with randomly generated numbers of small values( range from 0 to 127). The initially unsorted array is printed 
by the root process. Any process in the tree handles a chunk of the array denoted by L and R. For root process L=0 and R
=n-1. Any process in the tree first computes the number of integers in the chunk, if less than 10 then the process itself
calculates the maximum, prints it and exits. If chunk size is more than or equal to 10 then it creates two child process 
Pl and Pr which handles [L,M] and [M+,R] where M=(L+R)/2. P waits until the two child process has ended, then computes 
the maximum of the two values returned by its children and prints the result. Every non root process returns to its parent 
via the exit() call the maximum value calculated by it. During printing the maximum value by a process P display its PID 
and also its Parent PID.*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
int getmax(int *a,int l,int r)
{
	if((r-l+1)<10)
	{
		int i;
		//print process id and parent process id of this chunk which is less than 10
		printf("process id =%u parent process id =%u  ",getpid(),getppid());
		//calculate max 
		int max=a[l];
		for(i=l+1;i<=r;i++)
		if(max<a[i])
		max=a[i];
		
		printf("max found=%d\n",max);
		return max;
	}
	// now we need to fork() since chunk is greater than or equal to 10
	int m=1,m2,mid=(r+l)/2;
	if(!fork())
	{
		//must be child
		m=getmax(a,l,mid);
		exit(m);
		//child will return the max calculated to parent
	}
	//must be parent
	int status=0;
	wait(&status);//wait for the child to end
	m2=WEXITSTATUS(status);//get the value returned by child 
	m=getmax(a,mid+1,r);//check for maximum in parent's chunk 
	return m>m2?m:m2;//return the value which is larger
}
int main()
{
	int n,*a,i,pid;
	scanf("%d",&n);
	a=(int *)malloc(n*sizeof(int));
	srand(15);//seed for random numbers 
	for(i=0;i<n;i++)
	a[i]=rand()%128;//range 0 to 127


	pid=(int)getpid();
	printf("STARTING PROCESS ID = %d \n",pid);


	printf("entered numbers are \n");
	for(i=0;i<n;i++)
	printf("%d ",a[i]);
	printf("\n");


	printf("FINALLY MAXIMUM  is %d\n",getmax(a,0,n-1));
	return 0;
}
