#include<func.h>
int pid;
int msqid;
int fdr,fdw;
struct msgbuf{
	long mtype;
	char mtext[512];
};
struct msgbuf msg;
void sighFunc(int sighid)
{
	kill(pid,SIGINT);
	close(fdr);
	close(fdw);
	msg.mtype = 3;
	msgsnd(msqid,&msg,sizeof(msg.mtext),0);
	usleep(5000);
	msgctl(msqid,IPC_RMID,NULL);
	exit(0);
}

int main(int argc,char *argv[])
{
	signal(SIGINT,sighFunc);
	ARGS_CHECK(argc,3);
	fdw = open(argv[1],O_WRONLY);
	fdr = open(argv[2],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	ERROR_CHECK(fdw,-1,"open1");
	int ipid = getpid();
	write(fdw,&ipid,sizeof(int));
	read(fdr,&pid,sizeof(int));
	printf("read fdw = %d,fdr = %d\n",fdw,fdr);
	msqid = msgget(1000,0600|IPC_CREAT);
	bzero(&msg,sizeof(msg));
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
				memset(msg.mtext,0,sizeof(msg.mtext));
				ret =read(fdr,msg.mtext,sizeof(msg.mtext));
				msg.mtype = 1;
				msgsnd(msqid,&msg,sizeof(msg.mtext),0);
				if(ret == 0)
				{
					kill(getpid(),SIGINT);
					break;
				}
			}
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				memset(msg.mtext,0,sizeof(msg.mtext));
				ret =read(0,msg.mtext,sizeof(msg.mtext));
				msg.mtype = 2;
				msg.mtext[strlen(msg.mtext)-1] = '\0';
				msgsnd(msqid,&msg,sizeof(msg.mtext),0);
				if(ret == 0)
				{
					kill(getpid(),SIGINT);
					break;
				}
				write(fdw,msg.mtext,strlen(msg.mtext));
			}
		}
	}
	return 0;
}


