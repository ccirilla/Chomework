#include <func.h>

#define N 20000000
int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	int *pShm = (int*)shmat(shmid,NULL,0);
	ERROR_CHECK(shmid,-1,"shmget");
	*pShm = N;
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
	int i =0;
	if(!fork())
	{
		while(1)
		{
			semop(semid,&sopp,1);
			if(*pShm >0)
			{	
				(*pShm)--;
				i++;
				semop(semid,&sopv,1);
			}else
			{	
				semop(semid,&sopv,1);
				break;
			}
		}
		gettimeofday(&end,NULL);
		printf("A站用时%ldus将票售空\nA站共售出%d张车票\n",
				(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec,i);
		shmdt(pShm);
	}
	else
	{
		while(1)
		{
			semop(semid,&sopp,1);
			if(*pShm >0)
			{	
				(*pShm)--;
				i++;
				semop(semid,&sopv,1);
			}else
			{	
				semop(semid,&sopv,1);
				break;
			}
		}
		gettimeofday(&end,NULL);
		printf("B站用时%ldus将票售空\nB站共售出%d张车票\n",
				(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec,i);
		shmdt(pShm);
	
		wait(NULL);
		shmdt(pShm);
		shmctl(shmid,IPC_RMID,NULL);
		semctl(semid,0,IPC_RMID);
	}
}


