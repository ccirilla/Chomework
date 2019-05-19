#include<func.h>
typedef struct msgbuf
{
	long mtype;
	char mtext[512];
};

int main()
{
	int msqid = msgget(1000,0600|IPC_CREAT);
	struct msgbuf msg;
	while(1)
	{
		msgrcv(msqid,&msg,sizeof(msg.mtext),0,0);
		switch (msg.mtype)
		{
			case 1:
		    	printf("%-63s\n",msg.mtext);
				continue;
			case 2:
		    	printf("%63s\n",msg.mtext);
				continue;
			case 3:
				printf("Bye ~ Bye ~~\n");
				exit(0);
		}
	}
	return 0;
}




