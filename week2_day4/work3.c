#include <func.h>
void sighfunc(int sighnum,siginfo_t *p,void *oldact)
{
	printf("sigh : %d is coming\n",sighnum);
	sleep(3);
	sigset_t at;
	sigpending(&at);
	if(sigismember(&at,SIGQUIT))
		printf("3号信号被阻塞了，我马上挂了\n");
	else
		printf("3号信号没来。\n");
	printf("sigh : %d is leving\n",sighnum);
}

int main()
{
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction = sighfunc;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);
	sigaction(SIGINT,&act,NULL);
	while(1);
	return 0;
}


