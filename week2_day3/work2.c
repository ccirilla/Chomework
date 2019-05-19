#include <func.h>

#define N 10000000
int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	int *pShm = (int*)shmat(shmid,NULL,0);
	ERROR_CHECK(shmid,-1,"shmget");
	*pShm = 0;
	int semid = semget(1000,1,0600|IPC_CREAT);
	ERROR_CHECK(semid,-1,"semget");
	int ret = semctl(semid,0,SETVAL,1);
	ERROR_CHECK(ret,-1,"semctl");
	struct sembuf sopp,sopv;
	sopp.sem_num = 0;sopv.sem_num =0;
	sopp.sem_op = -1;sopv.sem_op = 1;
	sopp.sem_flg = 0;sopv.sem_flg = 0;
	struct timeval start,end;
	gettimeofday(&start,NULL);
	if(!fork())
	{
		for(int i=0;i<N;i++)
		{
			semop(semid,&sopp,1);
			(*pShm) ++;
			semop(semid,&sopv,1);
		}
		shmdt(pShm);
	}
	else
	{
		for(int i=0;i<N;i++)
		{
			semop(semid,&sopp,1);
			(*pShm) ++;
			semop(semid,&sopv,1);
		}
		wait(NULL);
		gettimeofday(&end,NULL);
		printf("result = %d\nuse time = %ldus\n",*pShm,
				(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
		shmdt(pShm);
		shmctl(shmid,IPC_RMID,NULL);
		semctl(semid,0,IPC_RMID);
	}
}

