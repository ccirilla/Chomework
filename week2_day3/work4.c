#include <func.h>

#define N 20000000
int main()
{
	int semid = semget(1000,2,0600|IPC_CREAT);
	ERROR_CHECK(semid,-1,"semget");
	int ret = semctl(semid,0,SETVAL,0);//第一个信号量为仓库容量
	ERROR_CHECK(ret,-1,"semctl");
   	ret = semctl(semid,1,SETVAL,10);//第二个信号量为产品数量
	ERROR_CHECK(ret,-1,"semctl");
	struct sembuf sopp,sopv;
	if(!fork())//生产者
	{
		sopp.sem_num = 0;sopv.sem_num =1;
		sopp.sem_op = -1;sopv.sem_op = 1;
		sopp.sem_flg = 0;sopv.sem_flg = 0;
		while(1)
		{
			printf("\n\nbefore produce \n");
			printf("productor number is %d   space number is %d\n",
					semctl(semid,1,GETVAL),semctl(semid,0,GETVAL));
			semop(semid,&sopp,1);
			printf("now producing......\n");
			semop(semid,&sopv,1);
			printf("productor number is %d   space number is %d\n",
					semctl(semid,1,GETVAL),semctl(semid,0,GETVAL));
			sleep(2);
		}
	}
	else//消费者
	{
		sopp.sem_num = 1;sopv.sem_num =0;
		sopp.sem_op = -1;sopv.sem_op = 1;
		sopp.sem_flg = 0;sopv.sem_flg = 0;
		while(1)
		{
			printf("\n\nbefore consume \n");
			printf("productor number is %d   space number is %d\n",
					semctl(semid,1,GETVAL),semctl(semid,0,GETVAL));
			semop(semid,&sopp,1);
			printf("now consume......\n");
			semop(semid,&sopv,1);
			printf("productor number is %d   space number is %d\n",
					semctl(semid,1,GETVAL),semctl(semid,0,GETVAL));
			sleep(1);
		}
		wait(NULL);
		semctl(semid,0,IPC_RMID);
	}
}


