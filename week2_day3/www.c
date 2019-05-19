#include <func.h>

struct msgbuf
{
	long mtype;
	char mtext[1];
};

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	struct msgbuf *msg = (struct msgbuf*)calloc(1,100);
	int msgid = msgget(1000,0600|IPC_CREAT);
	msg->mtype = atol(argv[1]);
	strcpy(msg->mtext,argv[2]);
	int ret = msgsnd(msgid,msg,strlen(msg->mtext),0);
	ERROR_CHECK(ret,-1,"msgsnd");
	return 0;
}


