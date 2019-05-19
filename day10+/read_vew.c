#include<func.h>
typedef struct info
{
	int flag;
	char buf[512];
}info;

int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	info *pShm = (info*)shmat(shmid,NULL,0);
	while(1)
	{
		switch (pShm->flag)
		{
			case 0:continue;
			case 1:
		    	printf("%-63s\n",pShm->buf);
				pShm->flag = 0;
				continue;
			case 2:
		    	printf("%63s\n",pShm->buf);
				pShm->flag = 0;
				continue;
			case 3:
				 printf("Bye ~ Bye ~~\n");
				 shmdt(pShm);
                 exit(0);
		}
	}
}



