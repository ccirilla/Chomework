#include <func.h>

int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	char *pShm = (char *)shmat(shmid,NULL,0);
	strcpy(pShm,"How are you");
	shmdt(pShm);
	return 0;
}
