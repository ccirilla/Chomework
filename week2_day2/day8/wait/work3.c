#include <func.h>
int add(int a,int b)
{

	for(int i =1;i<10;i++)
		a +=b;
	return a;
}
#define N 100000000
int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	int *pShm = (int *)shmat(shmid,NULL,0);
	*pShm = 0;
	pShm[1] = 0;
	int i = 0;
	if(!fork())
	{
		while(i<N)
		{
			if(*pShm == 0)
			{
				*pShm =11;	
				add(i,i+1);
				if(*pShm == 11)
				{
					pShm[1] += 1;
					i++;
					*pShm = 0;
				}
			}
		}
		shmdt(pShm);
		exit(0);
	}
	else
	{
		while(i<N)
		{
			if(*pShm == 0)
			{
				*pShm =22;	
				add(i,i+1);
				if(*pShm == 22)
				{
					pShm[1] += 1;
					i++;
					*pShm = 0;
				}
			}
		}
		wait(NULL);
		printf("%d\n",pShm[1]);
		shmdt(pShm);
		shmctl(shmid,IPC_RMID,NULL);
	}
	return 0;
}
