#include <func.h>
void sighfunc(int sighnum,siginfo_t *p,void *oldact)
{
	printf("sigh : %d is coming\n",sighnum);
	sleep(3);
	printf("sigh : %d is leving\n",sighnum);
}

int main()
{
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_flags=SA_SIGINFO|SA_NODEFER;
	act.sa_sigaction = sighfunc;
	sigaction(SIGINT,&act,NULL);
	sigaction(SIGQUIT,&act,NULL);
	while(1);
	return 0;
}


