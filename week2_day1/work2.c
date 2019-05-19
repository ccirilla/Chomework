#include<func.h>

int main(void)
{
	printf("begin!-----------\n");
	int ret = fork();
	if(ret == 0)
	{
		printf("I am son process PID = %d\n",getpid());
		while(1);
	}
	else
	{

		printf("I am preant process PID = %d\n",getpid());
		while(1);
	}
}
