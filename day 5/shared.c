

/*
In this program you will write a program to solve the m-producer n-consumer problem, m,n>=1
You have a shared circular buffer that can hold 20 integers. Each of the producer processes stores
the numbers 1 to 50 in the buffere one by one( in a loop with 50 iterations) and then exits. Each
of the consumer processes rwads the numbers from the buffer and adds them to a shared variable
SUM(initialises to 0). Any consumer processes can read any of the numbers in the buffer. The only
constrain is that every number written by some producer should be read exactly once by exactly one
of the consumers. Of course, a producer should not write when buffer is full and a consumer should
not read when buffer is empty.

Write a code that first creates a shared circular buffer and shared variable SUM and accepts value 
m and n and then forks m producers and n consumers.You can create any other shared variable if you need. 
The producer and consumer codes can be written as a functions that are called by the child processes.
After all the producers and consumers have finished(the consumer exits after all the data produced by 
all the producers have been read. How does a consumer know this?), the parent process prints the value
of the SUM. Note that correct value of SUM should be m*25*51. Test your code with atleast 
(a)m=1,n=1 	(b)m=1,n=2	(c)m=2,n=1	(d)m=2,n=2
*/








#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main()
{
	int shmid,status;
	int *a,*b;
	int i,j,k;
	int m,n;


	printf("enter m & n\n");
	scanf("%d%d",&m,&n);
	shmid=shmget(IPC_PRIVATE, 21*sizeof(int), 0777|IPC_CREAT);
	for(k=0;k<m;k++)
	{
		if(!fork())
		{
			//child
			b=(int *)shmat(shmid,0,0);
			for(i=0;i<50;)
			{
				sleep(2);
				for(j=0;j<20 && i<50;j++)
				{
					b[20]=b[20]+b[j];
					i++;
					printf(" %d ",b[j]);
				}
				printf("\n");
			}

			shmdt(b);
			exit(0);
		}
		//parent

		a=(int *)shmat(shmid,0,0);
		for(i=0;i<50;)
		{
			sleep(2);
			for(j=0;j<20 && i<50;j++)
			{
				a[j]=(i+1);
				i++;
			}

		}
		wait(&status);
		printf(" sum in parent is = %d \n",a[20]);
		shmdt(a);
	}
	shmctl( shmid, IPC_RMID , 0 );

	return 0;
}

