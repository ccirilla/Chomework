#include<func.h>
int pid;
int fdw,fdr;
int shmid;
typedef struct info
{
	int flag;
	char buf[512];
}info;

info *pShm;

void sighFunc(int sighid)
{
	kill(pid,SIGINT);
	close(fdr);
	close(fdw);
	pShm->flag = 3;
	usleep(100000); 
	shmdt(pShm);
	shmctl(shmid,IPC_RMID,NULL);
	exit(0);
}


int main(int argc,char *argv[])
{
	signal(SIGINT,sighFunc);
	ARGS_CHECK(argc,3);
	fdr = open(argv[1],O_RDONLY);
	fdw = open(argv[2],O_WRONLY);
	ERROR_CHECK(fdr,-1,"open");
	ERROR_CHECK(fdw,-1,"open1");
	int ipid = getpid();                                                  
	read(fdr,&pid,sizeof(int));
	write(fdw,&ipid,sizeof(int));
	printf("read fdw = %d,fdr = %d\n",fdw,fdr);
	shmid = shmget(1000,4096,0600|IPC_CREAT);
	pShm = (info*)shmat(shmid,NULL,0);
	bzero(pShm,sizeof(info));
	fd_set rdset;
	int ret;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(fdr,&rdset);
		ret = select(fdr+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(fdr,&rdset))
			{
				//	memset(buf,0,sizeof(buf));
				//	ret =read(fdr,buf,sizeof(buf));
				bzero(pShm->buf,sizeof(pShm->buf));
				ret =read(fdr,pShm->buf,sizeof(pShm->buf));
				pShm->flag =1;
				if(ret == 0)
				{
					kill(getpid(),SIGINT);
					break;
				}
			}
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				//memset(buf,0,sizeof(buf));
				//ret=read(0,buf,sizeof(buf));
				bzero(pShm->buf,sizeof(pShm->buf));
				ret=read(0,pShm->buf,sizeof(pShm->buf));
				pShm->buf[strlen(pShm->buf)-1] = '\0';
				pShm->flag =2;
				if(ret == 0)
				{
					kill(getpid(),SIGINT);
					break;
				}
				//write(fdw,buf,strlen(buf)-1);
				write(fdw,pShm->buf,strlen(pShm->buf));
			}
		}
	}
	return 0;
}


