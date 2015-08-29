/* Create a list of maximum 100 elements. Search for an element in the list. Create two child process to search the list . Each child process searches in each half and if element is found returns the array index. If element is not found then it will return -1 to signify element is not present. */




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
	printf("enter number of elements and the elements\n");
	scanf("%d",&size);
	for(i=0;i<size;i++)
	scanf("%d",&a[i]);
	printf("enter element to be searched\n");
	scanf("%d",&n);
	if(!fork())
	{
		// first child
		int m=search(a,0,n=size/2,n);
		exit(m);//return search result
	}
	int status=0;
	wait(&status);
	int pos1=WEXITSTATUS(status);
	if(pos1>=0 && pos1<=size/2)
	printf("Element found at array index =%d\n",pos1);
	else
	{
		if(!fork())
		{
			//second child 
			int m2=search(a,size/2+1,size-1,n);
			exit(m2);
		}
		int status2=0;
		wait(&status2);
		int pos2=WEXITSTATUS(status2);
		if(pos2>=(size/2+1) && pos2<=(size-1))
		printf("Element found at array index =%d\n",pos2);
		else 
		printf("Element not found\n ");
	}
	return 0;
}





