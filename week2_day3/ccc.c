#include <func.h>

struct msgbuf
{
	long mtype;
	char mtext[1];
};

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	struct msgbuf *msg = (struct msgbuf*)calloc(1,100);
	int msgid = msgget(1000,0600|IPC_CREAT);
	int ret = msgrcv(msgid,msg,sizeof(struct msgbuf),atol(argv[1]),0);
	ERROR_CHECK(ret,-1,"msgsnd");
	printf("%s\n",msg->mtext);
	return 0;
}


