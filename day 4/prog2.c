/* Create a list of maximum 100 elements. Search for an element in the list. Create two child process to search the list . Each child process searches in each half and if element is found returns the array index. If element is not found then it will return -1 to signify element is not present. */

/* Achieve this with the help of pipes */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define SIZE 100

int search(int *a,int start,int end,int ele)
{
	int i;
	for(i=start;i<=end;i++)
	if(a[i]==ele)
	return i;
	return -1;//if not found
}


int main()
{


	int size,a[100],n,i;
	int fd[2];// for reading and writing
	char line[SIZE];




	printf("enter number of elements and the elements\n");
	scanf("%d",&size);
	for(i=0;i<size;i++)
	scanf("%d",&a[i]);
	printf("enter element to be searched\n");
	scanf("%d",&n);

//------------------------------------------------------------------------------------------------------------------


	pipe(fd); /* fd[0] for reading
		     fd[1] for writing */
	if(!fork())
	{
		// first child
		close(fd[0]); //v child will not read hence we close fd[0]
		int m=search(a,0,n=size/2,n);
		sprintf(line,"%d",m);
		write(fd[1],line,SIZE);
		sleep(2);
		exit(0);// stop child
	}

	close(fd[1]); //parent will only read from pipe
	read(fd[0],line,SIZE);
	int pos1;
	sscanf(line,"%d",&pos1);

	if(pos1>=0 && pos1<=size/2)
	printf("Element found at array index =%d\n",pos1);
	else
	{
		pipe(fd);

		if(!fork())
		{
			//second child
			close(fd[0]); // child will not read so close fd[0]
			int m2=search(a,size/2+1,size-1,n);
			sprintf(line,"%d",m2);
			write(fd[1],line,SIZE);
			sleep(2);
			exit(0);//stop child
		}


		close(fd[1]); //parent will only read from pipe
		read(fd[0],line,SIZE);
		int pos2;
		sscanf(line,"%d",&pos2);


		if(pos2>=(size/2+1) && pos2<=(size-1))
		printf("Element found at array index =%d\n",pos2);
		else
		printf("Element not found\n ");
	}
	return 0;
}





