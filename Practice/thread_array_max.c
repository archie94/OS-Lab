/* Find the maximum in an array using 2 threads and searching both halfs simultaneously */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *arr;

struct data
{
	int start,end;
	int max;
};

void* max_runner(void *arg)
{
	struct data *curData = (struct data *)arg;
	int i,max=0;
	for(i=curData->start;i<=curData->end;i++)
	{
		if(arr[i]>max)
		max=arr[i];
	}
	curData->max = max;
}

int main()
{
	int i,n;
	scanf("%d",&n);
	arr = (int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	scanf("%d",&arr[i]);

	struct data d1,d2;
	d1.start = 0;
	d1.end = n/2;
	d2.start = n/2+1;
	d2.end = n-1;
	pthread_t tid1,tid2;
	pthread_attr_t attr1,attr2;


	pthread_attr_init(&attr1);
	pthread_create(&tid1,&attr1,max_runner,&d1);

	pthread_attr_init(&attr2);
	pthread_create(&tid2,&attr2,max_runner,&d2);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	if(d1.max>d2.max)
	printf("%d\n",d1.max);
	else
	printf("%d\n",d2.max);

	return 0;
}

