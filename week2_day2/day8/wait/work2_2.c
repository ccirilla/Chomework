#include <func.h>

int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	char *pShm = (char *)shmat(shmid,NULL,0);
	printf("%s\n",pShm);
	shmdt(pShm);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
