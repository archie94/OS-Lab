//13/CS/26 and 13/CS/32
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(int argv,char *argc[])
{
	int i,n=argv;
	printf("EXECUTING HALF  PID of half is %d  ",getpid());
	int val=atoi(argc[n-1]);
	val=val/2;
	printf("value returned =%d\n",val);
	if(n>2)
	{
		int num=val,count=0;
		for(i=0;i<n-2;i++)
		{
			int len=strlen(argc[i+1]);
			len++;
			argc[i]=(char *)malloc(len*sizeof(char));
			int j;
			for(j=0;j<len-1;j++)
			argc[i][j]=argc[i+1][j];
			argc[i][len-1]=0;
		}
		argc[n-1]=NULL;
		while(num>0)
		{
			num/=10;
			count++;
		}
		count++;
		argc[n-2]=(char *)malloc(count*sizeof(char));
		count--;
		argc[n-2][count]=0;
		count--;
		while(val>0)
		{
			int r=val%10;
			argc[n-2][count]=(char)(r+48);
			count--;
			val/=10;
		}
		if(!strcmp(argc[0],"twice"))
		execvp("./twice",argc);
		else if(!strcmp(argc[0],"half"))
		execvp("./half",argc);
		else
		execvp("./square",argc);
	}
	return 0;
}

